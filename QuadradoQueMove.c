#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include<time.h>
int X = 45;
#define LARGURA_DO_MUNDO 100
#define ALTURA_DO_MUNDO 100

int keyboard[256];
float aspectratio = 0.7692;
typedef struct {
  double posx;
  double posy;
  double tamx;
  double tamy;
  int existe;
}objetos;
float W;
objetos coisas[100];
objetos anzol;
objetos fundo;
//coisas[1] = fundo;
int contobj = 1;
float yfundo = 0;
void desenhaQuadrado(void){
  glClear(GL_COLOR_BUFFER_BIT);
//desenhando o fundo cabuloso
glColor3f(1, 0, 0);
  glPushMatrix();
    glTranslatef(0,yfundo,0);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(-(coisas[0].tamx)/2, -(coisas[0].tamy)/2, 0);
      glColor3f(0, 1, 0);
      glVertex3f((coisas[0].tamx)/2, -(coisas[0].tamy)/2, 0);
      glColor3f(0, 0, 1);
      glVertex3f((coisas[0].tamx)/2, (coisas[0].tamy)/2, 0);
      glColor3f(1, 1, 0);
      glVertex3f(-(coisas[0].tamx)/2, (coisas[0].tamy)/2, 0);
    glEnd();
  glPopMatrix();
  //fim do desenho do fundo
  // Começa a usar a cor verde
  glColor3f(0, 1, 0);
  for(int x = 1;x<contobj;x++){
  if(coisas[x].existe){
    glPushMatrix();
      glTranslatef(coisas[x].posx,coisas[x].posy,0);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-(coisas[x].tamx)/2, -(coisas[x].tamy)/2, 0);
        glVertex3f((coisas[x].tamx)/2, -(coisas[x].tamy)/2, 0);
        glVertex3f((coisas[x].tamx)/2, (coisas[x].tamy)/2, 0);
        glVertex3f(-(coisas[x].tamx)/2, (coisas[x].tamy)/2, 0);
      glEnd();
    glPopMatrix();
  }
}
  glutSwapBuffers();
}
/*
void desenhaCena(void)
{
    // Limpa a tela (com a cor definida por glClearColor(R,G,B)) para que
    // possamos desenhar
    glClear(GL_COLOR_BUFFER_BIT);

    // Começa a usar a cor verde
    glColor3f(0, 1, 0);
    if(keyboard['a']){
      anzol.posx-=10;
    }
    if(keyboard['d']){
      anzol.posx+=10;
    }
    glPushMatrix();
      glTranslatef(anzol.posx,anzol.posy,0);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(-(anzol.tamx)/2, -(anzol.tamy)/2, 0);
      glVertex3f((anzol.tamx)/2, -(anzol.tamy)/2, 0);
      glVertex3f((anzol.tamx)/2, (anzol.tamy)/2, 0);
      glVertex3f(-(anzol.tamx)/2, (anzol.tamy)/2, 0);
    glEnd();
    glPopMatrix();
    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}
*/
// Inicia algumas variáveis de estado
void inicializa(void)
{
    // cor para limpar a tela
    glClearColor(1, 1, 1, 0);      // branco
    //criando o anzol
    anzol.posx = 0;
    anzol.posy = 72;
    anzol.tamx = 30;
    anzol.tamy = 30;
    anzol.existe = 1;
    coisas[1] = anzol;
    contobj ++;
    fundo.posx = 0;
    fundo.posy = 0;
    fundo.tamx = 500;
    fundo.tamy = 5000;
    fundo.existe = 1;
    coisas[0] = fundo;
}

// Callback de redimensionamento
void redimensiona(int w, int h)
{
       W = w;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -1, 1);
    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    int w2 = h*aspectratio;
  //  glutReshapeWindow(500, 500);
}

// Callback de evento de teclado
void teclado(unsigned char key, int x, int y)
{
    switch(key)
    {
    // Tecla ESC
    case 27:
        exit(0);
        break;
    case 'a':
    case 'A':
      keyboard['a'] = 1;
    break;

    case 'd':
        case 'D':
        keyboard['d'] = 1;
    break;

    default:

    break;
    }
}

void upteclado(unsigned char key, int x, int y)
{
  switch (key) {
    case 'a':
      case 'A':
      keyboard['a'] = 0;
    break;
    case 'd':
      case 'D':
      keyboard['d'] = 0;
    break;
  }
}
void atualiza()
{
  //movimento do anzol
  if(keyboard['a']){
    coisas[1].posx-=10;
  }
  if(keyboard['d']){
    coisas[1].posx+=10;
  }
  //desenha o anzol
  printf("%f\n",anzol.posx);
 yfundo +=10;
  //  desenhaCena();
  //  glutSwapBuffers();
    glutPostRedisplay();
    glutTimerFunc(25, atualiza, 0);


}
// Rotina principal
int main(int argc, char **argv)
{


    //fundo.posy =
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 650);
    glutInitWindowPosition(100, 100);

    // Abre a janela
    glutCreateWindow("Insira seu nome");
    inicializa();

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaQuadrado);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(upteclado);
    inicializa();
    glutTimerFunc(0, atualiza, 0);
  //

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
