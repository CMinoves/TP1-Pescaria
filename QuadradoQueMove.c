#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include<time.h>
int X = 45;
#define LARGURA_DO_MUNDO 100
#define ALTURA_DO_MUNDO 100

int keyboard[256];

struct objetos{
  double posx;
  double posy;
  double tamx;
  double tamy;
  int existe;
}anzol,fundo;
float W;
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

// Inicia algumas variáveis de estado
void inicializa(void)
{
    // cor para limpar a tela
    glClearColor(1, 1, 1, 0);      // branco
    //criando o anzol

}

// Callback de redimensionamento
void redimensiona(int w, int h)
{
    /*   glViewport(0, 0, w, h);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       glOrtho(0, 100, 0, 100, -1, 1);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity(); */
       W = w;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -1, 1);
    glViewport(0, 0, w, h);
/*
    float razaoAspectoJanela = ((float)w)/h;
    float razaoAspectoMundo = ((float) LARGURA_DO_MUNDO)/ ALTURA_DO_MUNDO;
    // se a janela está menos larga do que o mundo (16:9)...
    if (razaoAspectoJanela < razaoAspectoMundo)
    {
        // vamos colocar barras verticais (acima e abaixo)
        float hViewport = w / razaoAspectoMundo;
        float yViewport = (h - hViewport)/2;
        glViewport(0, yViewport, w, hViewport);
    }
    // se a janela está mais larga (achatada) do que o mundo (16:9)...
    else if (razaoAspectoJanela > razaoAspectoMundo)
    {
        // vamos colocar barras horizontais (esquerda e direita)
        float wViewport = ((float)h) * razaoAspectoMundo;
        float xViewport = (w - wViewport)/2;
        glViewport(xViewport, 0, wViewport, h);
    }
    else
    {
        glViewport(0, 0, w, h);
    }
    */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

    desenhaCena();
    glutPostRedisplay();
    glutTimerFunc(25, atualiza, 0);

}

// Rotina principal
int main(int argc, char **argv)
{


    anzol.posx = 0;
    anzol.posy = 72;
    anzol.tamx = 30;
    anzol.tamy = 30;
    anzol.existe = 1;

    fundo.posx = 50;
    fundo.tamx = 50;
    //fundo.posy =
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);

    // Abre a janela
    glutCreateWindow("Insira seu nome");
    inicializa();

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(upteclado);
    inicializa();
    glutTimerFunc(0, atualiza, 0);

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
