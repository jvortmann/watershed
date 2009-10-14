//Biblioteca para leitura de imagens DICOM
#include <itkGDCMImageIO.h>

//Biblioteca para geração da lista de nomes das séries DICOM
#include <itkGDCMSeriesFileNames.h>

//Bibliotecas para leitura e escrita de imagens (séries ou não)
#include <itkImageFileReader.h>
#include <itkImageSeriesReader.h>
#include <itkImageFileWriter.h>

//Bibliotecas para preprocessamento da imagens
#include <itkCurvatureAnisotropicDiffusionImageFilter.h>
#include <itkGradientMagnitudeImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkUnaryFunctorImageFilter.h>
#include <itkScalarToRGBPixelFunctor.h>
#include <itkAddImageFilter.h>
#include <itkLaplacianSharpeningImageFilter.h>
#include <itkInvertIntensityImageFilter.h>

//Biblioteca do filtro Watershed
#include <itkWatershedImageFilter.h>

#include <iostream>
#include <string>
using namespace std;

int main (int argc, char const *argv[])
{
	//Variaveis auxiliares
	string nome;
	nome.clear();
	
	//Define os tipos das imagens que serão utilizadas
	//Define os tipos necessários pra leitura e escrita da imagem Dicom
	typedef unsigned short																						DicomPixelType;
	const unsigned int 																								DicomDimension = 3;
	typedef itk::Image<DicomPixelType, DicomDimension>								DicomImageType;

	//Define os tipos necessários para as imagem utilizadas nos filtros
	typedef float																											FilterPixelType;
	const unsigned int																								FilterDimension = 3;
	typedef itk::Image<FilterPixelType, FilterDimension>							FilterImageType;

	//Define os tipos necessários para as imagens utilizadas no Watershed
	typedef unsigned long																							WatershedPixelType;
	const unsigned int																								WatershedDimension = 3;
	typedef itk::Image<WatershedPixelType, WatershedDimension>				WatershedImageType;
  typedef itk::Image<WatershedPixelType, WatershedDimension>				LabeledImageType;

	//Define os tipos necessários para imagem usada como máscara (colorida)
	typedef itk::RGBPixel<unsigned char>    													RGBPixelType;
	const unsigned int 																								RGBDimension	= 3;
  typedef itk::Image<RGBPixelType, RGBDimension>										RGBImageType;

	//Define os tipos necessários para salvar as imagens em png
	typedef unsigned short																						PNGPixelType;
	const unsigned int																								PNGDimension = 3;
	typedef itk::Image<PNGPixelType, PNGDimension>										PNGImageType;
	
	//Define os leitores que serão utilizados
	//Define o leitor da imagem Dicom (o primeiro parâmetro serve
	//como identificação do arquivo ou série de entrada)
	typedef itk::ImageSeriesReader<DicomImageType>										DicomReaderType;
	DicomReaderType::Pointer dicom_reader = DicomReaderType::New();

	//Define as interfaces pra leitura de imagens Dicom
	typedef itk::GDCMImageIO																					ImageIOType;
	ImageIOType::Pointer dicomIO = ImageIOType::New();
	dicom_reader->SetImageIO( dicomIO );
	
	//Define os escritores utilizados
	//Define o escritor de imagens Dicom
	typedef itk::ImageFileWriter<DicomImageType> 											DicomWriterType;
	DicomWriterType::Pointer dicom_writer = DicomWriterType::New();
	dicom_writer->SetImageIO ( dicomIO );
	nome.clear();
	nome.assign(argv[2]);
	nome.append("_1input.dcm");
	dicom_writer->SetFileName( nome );
	
	//Define o escritor para imagens dos filtros
	//Define o escritor para imagens do filtro de borramento (mantém as bordas)
	typedef itk::ImageFileWriter<PNGImageType>												DiffusionWriterType;
	DiffusionWriterType::Pointer diffusion_writer = DiffusionWriterType::New();
	nome.clear();
	nome.assign(argv[2]);
	nome.append("_2diffusion.dcm");
	diffusion_writer->SetFileName( nome );
	
	//Define o leitor de imagens do filtro de gradiente
	// USADO PARA SIMULAÇÃO!
	/*
	typedef itk::ImageFileReader<FilterImageType>										GradientReaderType;
	GradientReaderType::Pointer gradient_reader = GradientReaderType::New();
	gradient_reader->SetFileName( argv[1] );
	*/
	
	//Define o escritor para imagens do filtro de gradiente
	typedef itk::ImageFileWriter<PNGImageType>												GradientWriterType;
	GradientWriterType::Pointer gradient_writer = GradientWriterType::New();
	nome.clear();
	nome.assign(argv[2]);
	nome.append("_3gradient.dcm");
	gradient_writer->SetFileName( nome );
	
	// @TESTE Define o escritor para imagens do filtro de laplace
	typedef itk::ImageFileWriter<PNGImageType>												LaplaceWriterType;
	LaplaceWriterType::Pointer laplace_writer = LaplaceWriterType::New();
	nome.clear();
	nome.assign(argv[2]);
	nome.append("_4laplace.dcm");
	laplace_writer->SetFileName( nome );
	
	// @TESTE
	typedef itk::ImageFileWriter<PNGImageType>												AddWriterType;
	AddWriterType::Pointer add_writer = AddWriterType::New();
	nome.clear();
	nome.assign(argv[2]);
	nome.append("_5adder.dcm");
	add_writer->SetFileName( nome );
	
	// @TESTE
	typedef itk::ImageFileWriter<PNGImageType>												InverterWriterType;
	InverterWriterType::Pointer inverter_writer = InverterWriterType::New();
	nome.clear();
	nome.assign(argv[2]);
	nome.append("_6inverter.dcm");
	inverter_writer->SetFileName( nome );
		
	//Define o escritor para imagens do filtro de Watershed
	typedef itk::ImageFileWriter<PNGImageType>												WatershedWriterType;
	WatershedWriterType::Pointer watershed_writer = WatershedWriterType::New();
	//Foram comentados para simulação!
	nome.clear();
	nome.assign(argv[2]);
	nome.append("_7watershed.dcm");
	watershed_writer->SetFileName( nome );
	//	Uso exclusivo da simulação
	//	watershed_writer->SetFileName( argv[2] );

	//Define o escritor para imagens coloridas (utilizadas como máscara)
	typedef itk::ImageFileWriter<RGBImageType>												RGBWriterType;
	RGBWriterType::Pointer rgb_writer = RGBWriterType::New();
	nome.clear();
	nome.assign(argv[2]);
	nome.append("_8maks.png");
	rgb_writer->SetFileName( nome );

	//Define as interfaces entre os filtros
	//Transforma imagens Dicom (unsigned short) para imagens de entrada dos filtros (float)
	typedef itk::CastImageFilter<DicomImageType, FilterImageType>			DicomToFilterType;
	DicomToFilterType::Pointer dicom_to_filter_caster = DicomToFilterType::New();
	
	//Transforma imagens dos filtros (float) para imagens de entrada do Watershed (long int)
	typedef itk::CastImageFilter<FilterImageType, WatershedImageType>	FilterToWatershedType;
	FilterToWatershedType::Pointer filter_to_watershed_caster = FilterToWatershedType::New();
	
	//Transforma imagens do Watershed (long int) para imagens Dicom (unsigend short)
	typedef itk::CastImageFilter<WatershedImageType, DicomImageType>	WatershedToDicomType;
	WatershedToDicomType::Pointer watershed_to_dicom_caster = WatershedToDicomType::New();
	
	//Transforma imagens do Watershed (long int) para imagens Dicom (unsigend short)
	typedef itk::CastImageFilter<WatershedImageType, FilterImageType>	WatershedToFilterType;
	WatershedToFilterType::Pointer watershed_to_filter_caster = WatershedToFilterType::New();
	
	//Transforma imagens do filtro de borramento (float) para imagens PNG (unsigned short)
	typedef itk::CastImageFilter<FilterImageType, PNGImageType>				FilterToPNGType;
	FilterToPNGType::Pointer diffusion_to_png_caster = FilterToPNGType::New();
	FilterToPNGType::Pointer gradient_to_png_caster = FilterToPNGType::New();
	// @TESTE Usados para teste
	FilterToPNGType::Pointer laplace_to_png_caster = FilterToPNGType::New();
	FilterToPNGType::Pointer add_to_png_caster = FilterToPNGType::New();
	FilterToPNGType::Pointer inverter_to_png_caster = FilterToPNGType::New();
	
	//Transforma imagens watershed (long int) para imagens PNG (unsigned short)
	typedef itk::CastImageFilter<WatershedImageType, PNGImageType>		WatershedToPNGType;
	WatershedToPNGType::Pointer watershed_to_png_caster = WatershedToPNGType::New();
	
	//Define os filtros utilizados
	//Define o filtro de borramento (quem mantém bordas)
	typedef itk::CurvatureAnisotropicDiffusionImageFilter<FilterImageType, FilterImageType>  DiffusionFilterType;
	DiffusionFilterType::Pointer diffusion = DiffusionFilterType::New();

	//Define o filtro de gradiente
	typedef itk::GradientMagnitudeImageFilter<FilterImageType, FilterImageType>	GradientMagnitudeFilterType;
	GradientMagnitudeFilterType::Pointer gradient = GradientMagnitudeFilterType::New();
	
	//Define o Watershed
	typedef itk::WatershedImageFilter<WatershedImageType> WatershedFilterType;
	WatershedFilterType::Pointer watershed = WatershedFilterType::New(); //cria o filtro de watershed
	
	//Define o filtro que transforma a imagem 
	//das regiões em um imagem colorida
	typedef itk::Functor::ScalarToRGBPixelFunctor<unsigned long> ColorMapFunctorType;
  typedef itk::UnaryFunctorImageFilter<LabeledImageType, RGBImageType, ColorMapFunctorType> ColorMapFilterType;
  ColorMapFilterType::Pointer colormapper = ColorMapFilterType::New();

	// @TESTE
	typedef itk::LaplacianSharpeningImageFilter< FilterImageType, FilterImageType > 	LaplaceFilterType;
	LaplaceFilterType::Pointer laplace = LaplaceFilterType::New();
	
	// @TESTE
	typedef itk::InvertIntensityImageFilter< FilterImageType, FilterImageType > InvertFilterType;
	InvertFilterType::Pointer inverter =  InvertFilterType::New();
	
	// @TESTE
	typedef itk::AddImageFilter< FilterImageType, FilterImageType, FilterImageType > AddFilterType; 
	AddFilterType::Pointer add = AddFilterType::New();
	AddFilterType::Pointer add2 = AddFilterType::New();
	
	//Verifica se é uma pasta
	int i;
	for(i = 0; argv[1][i] != '\0'; ++i);
	
	if(argv[1][i-1] == '/'){
			// Inicio leitura da serie -> alterar a dimensao das imagens
			typedef itk::GDCMSeriesFileNames NamesGeneratorType; //define o tipo do gerador da lista de nomes
			NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New(); //cria um ponteiro para o tipo anterior
			nameGenerator->SetUseSeriesDetails( true ); //define o parâmetro para utilização dos detalhes da imagem DICOM (utiliza vários campos)
			nameGenerator->SetDirectory( argv[1] ); //obtém o nome do diretório da entrada padrão (como primeiro argumento)

			typedef std::vector< std::string > SeriesIdContainer; //cria um vetor de identificador
			const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs(); //obtém os id da série através do gerador de nomes
			SeriesIdContainer::const_iterator seriesItr = seriesUID.begin(); //define o início da série
			SeriesIdContainer::const_iterator seriesEnd = seriesUID.end(); //define o fim da série
			while( seriesItr != seriesEnd ){ 
				std::cout << seriesItr->c_str() << std::endl; //mostra os identificadores dos slices
				seriesItr++;
			}

			std::string seriesIdentifier;
			seriesIdentifier = seriesUID.begin()->c_str();

			typedef std::vector< std::string > FileNamesContainer; //define um tipo para a série de nomes
			FileNamesContainer fileNames;
			fileNames = nameGenerator->GetFileNames( seriesIdentifier ); //cria os nomes dos arquivos atráves do gerador de nomes e do identificadores da série

			dicom_reader->SetFileNames( fileNames ); //define os nomes para leitura
			// Fim Leitura da serie
	}
	else{
			dicom_reader->SetFileName( argv[1] );
	}
	
	// Foram comentados para a simulacao!
	diffusion->SetNumberOfIterations( 10 ); // 5 but used 10
	diffusion->SetTimeStep( 0.0625 ); //0.125 - 2D, 0.0625 - 3D
  diffusion->SetConductanceParameter( 10 ); // 3.0 but used 10
	watershed->SetLevel(atof(argv[3])); // 0.01
	watershed->SetThreshold(atof(argv[4])); // 0.05

// Exclusivo para simulaçao
//	diffusion->SetNumberOfIterations( 5 ); // 5
// 	diffusion->SetConductanceParameter( 3.0 ); // 3.0
//	diffusion->SetTimeStep( 0.625 ); //0.125 - 2D, 0.0625 - 3D
//	watershed->SetLevel( atof(argv[3])/100 ); // 0.01
//	watershed->SetThreshold( atof(argv[4])/100 ); // 0.05
	
	//Pipeline de processamento
	//Indica a conexão entre os filtros
	
//  Foram comentados para acelerar a simulação!
	dicom_to_filter_caster->SetInput( dicom_reader->GetOutput() );
	
	diffusion->SetInput( dicom_to_filter_caster->GetOutput() );
	diffusion_to_png_caster->SetInput( diffusion->GetOutput() );
	diffusion_writer->SetInput( diffusion_to_png_caster->GetOutput() );
	
	gradient->SetInput( diffusion->GetOutput() );
	gradient_to_png_caster->SetInput( gradient->GetOutput() );
	gradient_writer->SetInput ( gradient_to_png_caster->GetOutput() );
	
	// @TESTE
	laplace->SetInput( diffusion->GetOutput() );
	laplace_to_png_caster->SetInput( laplace->GetOutput() );
	laplace_writer->SetInput ( laplace_to_png_caster->GetOutput() );
	
	// @TESTE
	//	dicom_to_png_caster->SetInput ( dicom_reader->GetOutput() );
	add->SetInput1( laplace->GetOutput() ); 
	add->SetInput2( gradient->GetOutput() );
	add2->SetInput1( add->GetOutput() ); 
	add2->SetInput2( diffusion->GetOutput() );	
	//add_writer->SetInput ( add2->GetOutput() );
	add_to_png_caster->SetInput ( add2->GetOutput() );
	add_writer->SetInput ( add_to_png_caster->GetOutput() );
	
	inverter->SetInput( add2->GetOutput());
	inverter->SetMaximum(itk::NumericTraits<DicomPixelType>::max());
	inverter_to_png_caster->SetInput( inverter->GetOutput() );
	inverter_writer->SetInput(inverter_to_png_caster->GetOutput());

	//foi comentados para teste
	//filter_to_watershed_caster->SetInput( gradient->GetOutput() );
	//uso exclusivo para simulação
//	filter_to_watershed_caster->SetInput( gradient_reader->GetOutput() );
	
	// @TESTE
	filter_to_watershed_caster->SetInput( inverter->GetOutput() );
	
	watershed->SetInput( filter_to_watershed_caster->GetOutput() );
	watershed_to_png_caster->SetInput( watershed->GetOutput() );
	watershed_writer->SetInput( watershed_to_png_caster->GetOutput() );
//	watershed_to_dicom_caster->SetInput( watershed->GetOutput() );
	
	dicom_writer->SetInput( dicom_reader->GetOutput() );
	
	colormapper->SetInput(watershed->GetOutput());
	rgb_writer->SetInput(colormapper->GetOutput());
	
	try //tenta escrever a imagem
	{
// Foram comentados para acelerar a simulação!
		dicom_writer->Update();
		diffusion_writer->Update();
		gradient_writer->Update();
		watershed_writer->Update();
		//rgb_writer->Update();
		// @TESTE usado para teste
		laplace_writer->Update();
		add_writer->Update();
		inverter_writer->Update();
	}
	catch (itk::ExceptionObject &ex)
	{
		std::cout << ex << std::endl;
		return EXIT_FAILURE;
	}
	
	return 0;
}