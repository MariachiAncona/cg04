#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
//Variables de dibujo y manipulacion
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0, rotRodDer = 0, rotBraDer = 0;
float giroMonito = 0;
float manecillas = 0;


#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotRodDer;
	float rotBraDer;
	float rotInc;
	float rotInc2;//Editado
	float rotInc3;//Editado
	float giroMonito;
	float giroMonitoInc;
	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=0;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01


//NEW///////////////////////////7

CTexture textMesa;
CTexture textPata;
CTexture textWall;
CTexture textSilla;
CTexture textTecho;
CTexture textMarble;
CTexture textPiso;
CTexture textGlassWasser;
CTexture textBarrote;
CTexture textCuadro1;
CTexture textMarco;
CTexture textLibroCG;
CTexture textPB;
CTexture textPuerta;
CTexture textPuerta_princ;
CTexture textMarco_1;
CTexture textMarco_2;
CTexture textMarco_3;
CTexture textGrass;
CTexture textSky;
CTexture textLibrero;

///////Texturas simon

CTexture aguaG;
CTexture alfombra;
CTexture baseGarrafon;
CTexture bocina;
CTexture hoja;
CTexture colchon;
CTexture libro;
CTexture maderaAzul;
CTexture pTapiz;
CTexture tMaceta;
CTexture tSillon;
CTexture mReloj;



//***ROSE****
CTexture textAlmohada;
CTexture textColcha;
CTexture textMaderaBuro;
CTexture textMaderaCama;
CTexture textLampara;
CTexture textLaptop;
CTexture textPantalla;
CTexture textTeclado;
CTexture textTouchPad;
CTexture textGW;

//CFiguras fig1;
//CFiguras fig5;
CFiguras tablaMesa;
CFiguras pata1Mesa;
CFiguras pata2Mesa;
CFiguras pata3Mesa;
CFiguras pata4Mesa;
CFiguras asientoSilla;
CFiguras respaldoSilla1;
CFiguras respaldoSilla2;
CFiguras respaldoSilla3;
CFiguras respaldoSilla4;
CFiguras techoCasa;
CFiguras pisoCasa;
CFiguras cubo;
CFiguras sky;
//*****ROSE*****

//Figuras simon
CFiguras paredes;
CFiguras ccalentador;
CFiguras ccama;
CFiguras cmaceta;
CFiguras cgarrafon;
CFiguras creloj;
CFiguras clibrero;
CFiguras csillon;

CFiguras buro;
CFiguras cono;
CFiguras lampara;
CFiguras laptop;

float abrirPuerta = 0;
//END NEW//////////////////////////////////////////

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito


void saveFrame ( void )
{
	
	printf("frameindex %d\n",FrameIndex);			

	KeyFrame[FrameIndex].posX=30;
	KeyFrame[FrameIndex].posY=30;
	KeyFrame[FrameIndex].posZ=30;

	KeyFrame[FrameIndex].rotRodIzq=50;
	KeyFrame[FrameIndex].rotRodDer = 50;//Editado
	KeyFrame[FrameIndex].rotBraDer = 50;
	KeyFrame[FrameIndex].giroMonito=50;
			
	FrameIndex++;
}

void resetElements( void )
{
	posX=KeyFrame[0].posX;
	posY=KeyFrame[0].posY;
	posZ=KeyFrame[0].posZ;

	rotRodIzq=KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;//Editado
	rotBraDer = KeyFrame[0].rotBraDer;//Editado
	giroMonito=KeyFrame[0].giroMonito;

}

void interpolation ( void )
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;	
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;	
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;	

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;

	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;//Editado

	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBraDer - KeyFrame[playIndex].rotBraDer) / i_max_steps;//

	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}


void ciudad ()
{

		glPushMatrix(); //Camino1
			glTranslatef(23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino2
			glTranslatef(-23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,-4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,7.0);
			glRotatef(90,1,0,0);
			glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,-7.0);
			glRotatef(90,1,0,0);
			//glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		fig7.prisma(2.0 ,2.0 ,1 ,text2.GLindex);

		glPushMatrix();//Cuello
			glTranslatef(0, 1.0, 0.0);
			fig7.cilindro(0.25, 0.25, 15, 0);
			glPushMatrix();//Cabeza
				glTranslatef(0, 1.0, 0);
				fig7.esfera(0.75, 15, 15, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho-->
			glTranslatef(1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(0.25, 0, 0);
				glRotatef(-45+rotBraDer, 0, 1, 0); //Editado
				glTranslatef(0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <--
			glTranslatef(-1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(-0.25, 0, 0);
				glRotatef(45, 0, 1, 0); 
				glRotatef(25, 0, 0, 1);
				glRotatef(25, 1, 0, 0); 
				glTranslatef(-0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
			glColor3f(0, 0, 1);
			glTranslatef(0, -1.5, 0);
			fig7.prisma(1, 2, 1, 0);

			glPushMatrix(); //Pie Derecho -->
				glTranslatef(0.75, -0.5, 0);
				glRotatef(-15, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15+rotRodDer, 1, 0, 0);// Editado
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


			glPushMatrix(); //Pie Izquierdo -->
				glTranslatef(-0.75, -0.5, 0);
				glRotatef(-5, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15+rotRodIzq, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

//END CASA////////////////////////////////////


void plano()
{
	glDisable(GL_LIGHTING);
	glColor3f(0.95, 0.95, 0.95);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -1);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(0, 1, -1);
	glEnd();
	glEnable(GL_LIGHTING);

}

GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();


	//NEW////////////////////////////////////////////

	textMesa.LoadBMP("casa/wood_5.bmp");
	textMesa.BuildGLTexture();
	textMesa.ReleaseImage();

	textPata.LoadBMP("casa/brick_3.bmp");
	textPata.BuildGLTexture();
	textPata.ReleaseImage();

	textWall.LoadBMP("casa/brick_2.bmp");
	textWall.BuildGLTexture();
	textWall.ReleaseImage();

	textSilla.LoadBMP("casa/madera.bmp");
	textSilla.BuildGLTexture();
	textSilla.ReleaseImage();
	
	textTecho.LoadBMP("casa/brick_3.bmp");
	textTecho.BuildGLTexture();
	textTecho.ReleaseImage();

	textMarble.LoadBMP("casa/marble_2.bmp");
	textMarble.BuildGLTexture();
	textMarble.ReleaseImage();

	textPiso.LoadBMP("casa/floor-parquet.bmp");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	textGlassWasser.LoadBMP("casa/glass_2.bmp");
	textGlassWasser.BuildGLTexture();
	textGlassWasser.ReleaseImage();

	textBarrote.LoadBMP("casa/brickwall.bmp");
	textBarrote.BuildGLTexture();
	textBarrote.ReleaseImage();

	textCuadro1.LoadBMP("casa/cuadro_1.bmp");
	textCuadro1.BuildGLTexture();
	textCuadro1.ReleaseImage();

	textMarco.LoadBMP("casa/burned wood.bmp");
	textMarco.BuildGLTexture();
	textMarco.ReleaseImage();

	textLibroCG.LoadBMP("casa/gc_donald.bmp");
	textLibroCG.BuildGLTexture();
	textLibroCG.ReleaseImage();

	textPuerta.LoadBMP("casa/door_3.bmp");
	textPuerta.BuildGLTexture();
	textPuerta.ReleaseImage();

	textPuerta_princ.LoadBMP("casa/door_3_4_puerta.bmp");
	textPuerta_princ.BuildGLTexture();
	textPuerta_princ.ReleaseImage();

	textMarco_1.LoadBMP("casa/door_3_1_izq.bmp");
	textMarco_1.BuildGLTexture();
	textMarco_1.ReleaseImage();

	textMarco_2.LoadBMP("casa/door_3_2_der.bmp");
	textMarco_2.BuildGLTexture();
	textMarco_2.ReleaseImage();

	textMarco_3.LoadBMP("casa/door_3_3_cen.bmp");
	textMarco_3.BuildGLTexture();
	textMarco_3.ReleaseImage();

	textGrass.LoadBMP("casa/grass_2.bmp");
	textGrass.BuildGLTexture();
	textGrass.ReleaseImage();

	textSky.LoadBMP("casa/blue-sky-texture.bmp");
	textSky.BuildGLTexture();
	textSky.ReleaseImage();

	textLibrero.LoadBMP("casa/strata.bmp");
	textLibrero.BuildGLTexture();
	textLibrero.ReleaseImage();

	textGW.LoadBMP("casa/glass window.bmp");
	textGW.BuildGLTexture();
	textGW.ReleaseImage();
	
	//*****ROSE******
	textAlmohada.LoadBMP("casa/almohada.bmp");
	textAlmohada.BuildGLTexture();
	textAlmohada.ReleaseImage();

	textColcha.LoadBMP("casa/colcha.bmp");
	textColcha.BuildGLTexture();
	textColcha.ReleaseImage();

	textMaderaBuro.LoadBMP("casa/buro.bmp");
	textMaderaBuro.BuildGLTexture();
	textMaderaBuro.ReleaseImage();

	textMaderaCama.LoadBMP("casa/maderaCama.bmp");
	textMaderaCama.BuildGLTexture();
	textMaderaCama.ReleaseImage();

	textLampara.LoadBMP("casa/lampara.bmp");
	textLampara.BuildGLTexture();
	textLampara.ReleaseImage();

	textLaptop.LoadBMP("casa/laptop.bmp");
	textLaptop.BuildGLTexture();
	textLaptop.ReleaseImage();

	textPantalla.LoadBMP("casa/windows.bmp");
	textPantalla.BuildGLTexture();
	textPantalla.ReleaseImage();

	textTeclado.LoadBMP("casa/tecla.bmp");
	textTeclado.BuildGLTexture();
	textTeclado.ReleaseImage();

	textTouchPad.LoadBMP("casa/touchpad.bmp");
	textTouchPad.BuildGLTexture();
	textTouchPad.ReleaseImage();


	//SIMON////////////////////////////////////////////

	aguaG.LoadTGA("aguaG.tga");
	aguaG.BuildGLTexture();
	aguaG.ReleaseImage();

	alfombra.LoadTGA("alfombra.tga");
	alfombra.BuildGLTexture();
	alfombra.ReleaseImage();

	baseGarrafon.LoadTGA("baseGarrafon.tga");
	baseGarrafon.BuildGLTexture();
	baseGarrafon.ReleaseImage();

	bocina.LoadTGA("bocina.tga");
	bocina.BuildGLTexture();
	bocina.ReleaseImage();

	colchon.LoadTGA("colchon.tga");
	colchon.BuildGLTexture();
	colchon.ReleaseImage();

	hoja.LoadTGA("hoja.tga");
	hoja.BuildGLTexture();
	hoja.ReleaseImage();

	libro.LoadTGA("libro.tga");
	libro.BuildGLTexture();
	libro.ReleaseImage();

	maderaAzul.LoadTGA("maderaAzul.tga");
	maderaAzul.BuildGLTexture();
	maderaAzul.ReleaseImage();

	mReloj.LoadTGA("mReloj.tga");
	mReloj.BuildGLTexture();
	mReloj.ReleaseImage();

	pTapiz.LoadTGA("pTapiz.tga");
	pTapiz.BuildGLTexture();
	pTapiz.ReleaseImage();

	tMaceta.LoadTGA("tMaceta.tga");
	tMaceta.BuildGLTexture();
	tMaceta.ReleaseImage();

	tSillon.LoadTGA("tSillon.tga");
	tSillon.BuildGLTexture();
	tSillon.ReleaseImage();

	//END NEW//////////////////////////////

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotInc = 0;
		KeyFrame[i].rotRodDer = 0;//Editado
		KeyFrame[i].rotInc2 = 0;
		KeyFrame[i].rotBraDer = 0;//Editado
		KeyFrame[i].rotInc3 = 0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void recamara()
{
	glPushMatrix();
	paredes.prisma(0.1,15,15,alfombra.GLindex);
	glTranslatef(7.5,7.5,0);
	paredes.prisma(15, 0.1, 15, pTapiz.GLindex);
	glTranslatef(-15, 0, 0);
	paredes.prisma(15, 0.1, 15, pTapiz.GLindex);
	glTranslatef(7.5,0,-7.5);
	paredes.prisma(15, 15, 0.1, pTapiz.GLindex);
	glTranslatef(0, 0, 15);
	paredes.prisma(15, 15, 0.1, pTapiz.GLindex);
	glTranslatef(0, 7.5, -7.5);
	paredes.prisma(0.1, 15, 15, textSky.GLindex);
	glTranslatef(-3, -0.5, 0);
	paredes.prisma(0.1, 0.1, 15, tMaceta.GLindex);
	glTranslatef(6, 0, 0);
	paredes.prisma(0.1, 0.1, 15, tMaceta.GLindex);
	glTranslatef(-3, 0, -3);
	paredes.prisma(0.1, 15, 0.1, tMaceta.GLindex);
	glTranslatef(0, 0, 6);
	paredes.prisma(0.1, 15, 0.1, tMaceta.GLindex);
	glPopMatrix();

}

void flecha(int giro)
{
	glRotatef(giro, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, -4.3);
	glRotatef(90, -1, 0, 0);
	creloj.cono(0.4, 0.2, 15, mReloj.GLindex);
	glPushMatrix();
	glTranslatef(0, -1.3, 0);
	creloj.cilindro(0.1, 1.5, 15, mReloj.GLindex);
	glPopMatrix();
	glPopMatrix();
}

void reloj()
{
	glRotatef(90,1,0,0);
	creloj.cilindro(3, 0.1, 23, mReloj.GLindex);

	/*glPushMatrix();
	glTranslatef(0, 0, -3.8);
	glRotatef(90, -1, 0, 0);
	creloj.cono(0.4,0.2,15,mReloj.GLindex);
		glPushMatrix();
		glTranslatef(0, -1.5, 0);
		creloj.cilindro(0.1, 1.5, 15, mReloj.GLindex);
		glPopMatrix();
	glPopMatrix();*/

	for (int i = 0; i < 360; i += 30) {
		flecha(i);
	}
	
	glPushMatrix();
	//glTranslatef(0, 0, 0.1);
	glRotatef(90,0,0,1);
	creloj.cono(2.4,0.1,15,hoja.GLindex);
	glPushMatrix();
	//glTranslatef(0, 0, 0.2);
	glRotatef(90, 1, 0, 0);
	creloj.cono(1.9, 0.1, 15, hoja.GLindex);
	glPopMatrix();
	glPopMatrix();

}

void sillon()
{
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1, 0, 0);
	csillon.cilindro(1, 1, 18, tSillon.GLindex);
	glTranslatef(1, 0, 0);
	csillon.cilindro(1, 1, 18, tSillon.GLindex);
	glTranslatef(1, 0, 0);
	csillon.cilindro(1, 1, 18, tSillon.GLindex);

	glPushMatrix();

	glRotatef(75, 1, 0, 0);
	glTranslatef(-0.9, -2, 0);
	glScalef(0.7,1,1);
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	csillon.cilindro(1, 1, 18, tSillon.GLindex);
	glTranslatef(1, 0, 0);
	csillon.cilindro(1, 1, 18, tSillon.GLindex);
	glTranslatef(1, 0, 0);
	csillon.cilindro(1, 1, 18, tSillon.GLindex);
	glPopMatrix();
	glPopMatrix();
	//Base
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(3.75,1.4,1);
	glTranslatef(-0.77,-0.4,-0.2);
	plano();
	glPopMatrix();
	//Derecha
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(1.1, 1.6, 1);
	glTranslatef(-0.2, -0.4, -2);
	plano();
	glPopMatrix();
	//Izquierda
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(1.3, 1.8, 1);
	glTranslatef(-0.2, -0.4, 2);
	plano();
	glPopMatrix();

}

void garrafon()
{	
	//Cuerpo
	glTranslatef(0, 1, 0);
	cgarrafon.cilindro(0.6,0.3,20,tMaceta.GLindex);

	//Patas
	glPushMatrix();
	glTranslatef(-0.3,0.3,0);
	glRotatef(180, 1, 0, 0);
	cgarrafon.cono(1.1,0.1,20,tMaceta.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.3);
	glRotatef(180, 1, 0, 0);
	cgarrafon.cono(1.1, 0.1, 20, tMaceta.GLindex);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.3, 0, 0.3);
	glRotatef(180, 1, 0, 0);
	cgarrafon.cono(1.1, 0.1, 20, tMaceta.GLindex);
	glPopMatrix();

	//Cuerpo
	glDisable(GL_LIGHTING);
	glColor3f(0.25, 0.65, 1);
	
	glPushMatrix();
	glTranslatef(0, 2.1, 0);
	glRotatef(180, 1, 0, 0);
	cgarrafon.cilindro(0.6, 1.8, 20, NULL);
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0, 1.1, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(1,5.5,1);
	cgarrafon.torus(0.8,0.6,20,20);
	glPopMatrix();
	glEnable(GL_LIGHTING);

}

void librero()
{
	glTranslatef(0,1,0);
	clibrero.prisma(0.1, 1, 1.5, maderaAzul.GLindex );
	//Repisas
	glPushMatrix();
	glTranslatef(0,1.5,0);
	clibrero.prisma(0.1, 1, 1.5, maderaAzul.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	clibrero.prisma(0.1, 1, 1.5, maderaAzul.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	clibrero.prisma(0.1, 1, 1.5, maderaAzul.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	clibrero.prisma(0.1, 1, 1.5, maderaAzul.GLindex);
	glPopMatrix();


	//Izquierdo
	glPushMatrix();
	glTranslatef(0, 0, -0.8);
	glRotatef(90,-1,0,0);
	clibrero.prisma(0.1, 1, 3.1, maderaAzul.GLindex);
	glPopMatrix();

	//Atras
	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	clibrero.prisma(3, 0.1, 1.7, maderaAzul.GLindex);
	glPopMatrix();

	//Derecho
	glPushMatrix();
	glTranslatef(0, 0,0.7);
	glRotatef(90,0,1,0);
	clibrero.prisma(3, 0.1, 1, maderaAzul.GLindex);
	glPopMatrix();

	//Bocinas

	glPushMatrix();
	glTranslatef(-0.4, -0.4, 0);
	//glRotatef(90, 0, 1, 0);
	clibrero.prisma(0.6, 0.1, 1.4, bocina.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, -1, 0);
	//glRotatef(90, 0, 1, 0);
	clibrero.prisma(0.6, 0.1, 1.4, bocina.GLindex);
	glPopMatrix();

	//libros
	glPushMatrix();
	glTranslatef(-0.4, 1.1, -0.3);
	//glRotatef(90, 0, 1, 0);
	clibrero.prisma(0.5, 0.4,0.1, libro.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 1.1, 0);
	//glRotatef(90, 0, 1, 0);
	clibrero.prisma(0.5, 0.4, 0.1, libro.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 1.1, 0.45);
	glRotatef(30, 1, 0, 0);
	clibrero.prisma(0.5, 0.4, 0.1, libro.GLindex);
	glPopMatrix();




}

void maceta()
{
	glPushMatrix();

	cmaceta.cilindro(2.4,2,20, tMaceta.GLindex);
		
		glTranslatef(0,2,0);
		glPushMatrix();
		cmaceta.cilindro(2.6, 0.6, 20, tMaceta.GLindex);
		glPopMatrix();

		glTranslatef(0, 0.7, 0);
		glPushMatrix();
		//glRotatef();
		//cmaceta.prisma(6.5,1.2,1.2,hoja.GLindex);
		cmaceta.cilindro(0.6, 6.5, 20, text5.GLindex);
		glPopMatrix();

		glTranslatef(0, 2.5, 1);
		glPushMatrix();
		glRotatef(60,1,0,0);
		cmaceta.prisma(2.5, 0.7, 0.7, text5.GLindex);
		glPopMatrix();

		glTranslatef(0, 1.9, -2.5);
		glPushMatrix();
		glRotatef(70, -1, 0, 0);
		cmaceta.prisma(2.5, 0.7, 0.7, text5.GLindex);
		glPopMatrix();
	
		

	glPopMatrix();
}

void camar()
{
	glPushMatrix();

	ccama.prisma(0.4, 7.5, 4, alfombra.GLindex);

		glTranslatef(0,0.5,0);
		glPushMatrix();
		ccama.prisma(0.4,7.5,3.5,alfombra.GLindex);
		glPopMatrix();

		//Colchon
		glTranslatef(0, 0.5, 0);
		glPushMatrix();
		ccama.prisma(1, 7, 3, colchon.GLindex);
		glPopMatrix();

		//Almohada
		glTranslatef(-2.3, 0.6, 0);
		glPushMatrix();
		ccama.prisma(0.3, 1.3, 2, textAlmohada.GLindex);
		glPopMatrix();



	glPopMatrix();
}

void calentador()
{
	glPushMatrix();
	glColor3f(0.5,0.5,0.5);

	ccalentador.prisma(5,5,2,NULL);
	
		glTranslatef(-2.1, 0, 0);
		glPushMatrix();
		glScalef(1,0.6,0.3);
		glRotatef(90,0,0,1);
		ccalentador.torus(5,5.5,15,15);
		glPopMatrix();

		glTranslatef(0.7, 0, 0);
		glPushMatrix();
		glScalef(1, 0.6, 0.3);
		glRotatef(90, 0, 0, 1);
		ccalentador.torus(5, 5.5, 15, 15);
		glPopMatrix();

		glTranslatef(0.7, 0, 0);
		glPushMatrix();
		glScalef(1, 0.6, 0.3);
		glRotatef(90, 0, 0, 1);
		ccalentador.torus(5, 5.5, 15, 15);
		glPopMatrix();

		glTranslatef(0.7, 0, 0);
		glPushMatrix();
		glScalef(1, 0.6, 0.3);
		glRotatef(90, 0, 0, 1);
		ccalentador.torus(5, 5.5, 15, 15);
		glPopMatrix();

		glTranslatef(0.7, 0, 0);
		glPushMatrix();
		glScalef(1, 0.6, 0.3);
		glRotatef(90, 0, 0, 1);
		ccalentador.torus(5, 5.5, 15, 15);
		glPopMatrix();

		glTranslatef(0.7, 0, 0);
		glPushMatrix();
		glScalef(1, 0.6, 0.3);
		glRotatef(90, 0, 0, 1);
		ccalentador.torus(5, 5.5, 15, 15);
		glPopMatrix();

		glTranslatef(0.7, 0, 0);
		glPushMatrix();
		glScalef(1, 0.6, 0.3);
		glRotatef(90, 0, 0, 1);
		ccalentador.torus(5, 5.5, 15, 15);
		glPopMatrix();

	glPopMatrix();
}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix();
	

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//CASA///////////////////
			//¨****casa*****
			glPushMatrix();
				glDisable(GL_LIGHTING);
					recamara();
					glPushMatrix();
					glTranslatef(-6, 1, -3);
					glScalef(0.2,0.2,0.2);
					calentador();
					glPopMatrix();
					//
					glPushMatrix();
					glTranslatef(0,1,-4);
					glScalef(1.2, 1, 1);
					camar();
					glPopMatrix();
					//
					glPushMatrix();
					glTranslatef(-6, 4.2, 4);
					glScalef(0.1, 0.1, 0.1);
					maceta();
					glPopMatrix();
					//
					glPushMatrix();
					glTranslatef(-6, 4.2, 4.7);
					glScalef(0.1, 0.1, 0.1);
					maceta();
					glPopMatrix();
					//
					glPushMatrix();
					glTranslatef(-6, 1, 1);
					glScalef(0.7, 0.7, 0.7);
					garrafon();
					glPopMatrix();
					//
					glPushMatrix();
					glTranslatef(-6, 1, 4);
					glRotatef(180, 0, 1, 0);
					glScalef(1.2, 1.2, 1.2);
					librero();
					glPopMatrix();
				//
					glPushMatrix();
					glTranslatef(7.3, 6, 5);
					glRotatef(90, 0, 1, 0);
					glScalef(0.4, 0.4, 0.4);
					reloj();
					glPopMatrix();
					//
					glPushMatrix();
					glTranslatef(6.3, 1, 5);
					glRotatef(90, 0, -1, 0);
					glScalef(1.1, 1.1, 1);
					sillon();
					glPopMatrix();
				
					glPopMatrix();
				

			glEnable(GL_LIGHTING);
			glPopMatrix();
					
			glColor3f(1.0,1.0,1.0);

		glPopMatrix();
	glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Proyecto Final");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.001;
	fig3.text_der-= 0.001;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	//Movimiento del monito
	if(play)
	{		
		
		if(	i_curr_steps >= i_max_steps) //end of animation between frames?
		{			
			playIndex++;		
			if(playIndex>FrameIndex-2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex=0;
				play=false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX+=KeyFrame[playIndex].incX;
			posY+=KeyFrame[playIndex].incY;
			posZ+=KeyFrame[playIndex].incZ;

			rotRodIzq+=KeyFrame[playIndex].rotInc;
			rotRodDer += KeyFrame[playIndex].rotInc2;//Editado
			rotBraDer += KeyFrame[playIndex].rotInc3;//Editado
			giroMonito+=KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}
		
	}


	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			printf("%f \n", rotRodIzq);
			break;

		case 'p':						
			giroMonito++;
			break;

		case 'P':						
			giroMonito--;
			break;
/////////////////////
		case 'n':
			rotRodDer++;
			printf("%f \n", rotRodDer);
			break;

		case 'N':
			rotRodDer--;
			printf("%f \n", rotRodDer);
			break;

		case 'm':
			rotBraDer++;
			printf("%f \n", rotBraDer);
			break;

		case 'M':
			rotBraDer--;
			printf("%f \n", rotBraDer);
			break;
///////////////////////////

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:	//Save KeyFrame
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 1:	//Play animation
			if(play==false)
			{

				resetElements();
				//First Interpolation
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;


	}
}

void menu( int id)
{
	
}



int main ( int argc, char** argv )   // Main Function
{
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);


  glutMainLoop        ( );          // 

  return 0;
}