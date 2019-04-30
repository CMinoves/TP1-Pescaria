#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include<time.h>
#include<SOIL/SOIL.h>
#include"QuadradoQueMove.c"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#define LARGURA_DO_MUNDO 100
#define ALTURA_DO_MUNDO 100
#define BOT_ALTURA 100
#define BOT_LARGURA 260
#define NUM_BOT 3
int egg;
int help;
GLuint fundao_textura;
GLuint ajudatela_textura;
GLuint novojogo_textura;
GLuint novojogo2_textura;
GLuint sair_textura;
GLuint sair2_textura;
GLuint ajuda_textura;
GLuint ajuda2_textura;
GLuint title_textura;
GLuint peixao_textura;
int op = 2;
objeto botao[NUM_BOT];
objeto fundao;
objeto title;
objeto peixao;
objeto ajuda;
objeto ajudaTela;


void desenhaAjuda(){
  glColor3f(1,1,1);
  glPushMatrix();
  glTranslatef(ajudaTela.posx,ajudaTela.posy,0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, ajudatela_textura);
  glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0,0);  glVertex3f(-(ajudaTela.tamx)/2, -(ajudaTela.tamy)/2, 0);
    glTexCoord2f(1,0);  glVertex3f((ajudaTela.tamx)/2, -(ajudaTela.tamy)/2, 0);
    glTexCoord2f(1,1);  glVertex3f((ajudaTela.tamx)/2, (ajudaTela.tamy)/2, 0);
    glTexCoord2f(0,1);  glVertex3f(-(ajudaTela.tamx)/2, (ajudaTela.tamy)/2, 0);
  glEnd();
  glPopMatrix();
}

void desenhaMenu(void){
  //printf("%i\n",egg);
  glClear(GL_COLOR_BUFFER_BIT);
  //desenhando o fundao cabuloso
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, fundao_textura);

  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(-(fundao.tamx)/2, -(fundao.tamy)/2, 0);
    glTexCoord2f(1,0); glVertex3f((fundao.tamx)/2, -(fundao.tamy)/2, 0);
    glTexCoord2f(1,1); glVertex3f((fundao.tamx)/2, (fundao.tamy)/2, 0);
    glTexCoord2f(0,1); glVertex3f(-(fundao.tamx)/2, (fundao.tamy)/2, 0);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  //desenhando o peixao
  glPushMatrix();
  glTranslatef(peixao.posx,peixao.posy,0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, peixao_textura);

  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(-(peixao.tamx)/2, -(peixao.tamy)/2, 0);
    glTexCoord2f(1,0); glVertex3f((peixao.tamx)/2, -(peixao.tamy)/2, 0);
    glTexCoord2f(1,1); glVertex3f((peixao.tamx)/2, (peixao.tamy)/2, 0);
    glTexCoord2f(0,1); glVertex3f(-(peixao.tamx)/2, (peixao.tamy)/2, 0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
glPopMatrix();

  if(help){
    desenhaAjuda();
  }else{
    //desenhando o título

    glPushMatrix();
      glTranslatef(title.posx,title.posy,0);
      glColor3f(1,1,1);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, title_textura);
      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);  glVertex3f(-(title.tamx)/2, -(title.tamy)/2, 0);
        glTexCoord2f(1,0);  glVertex3f((title.tamx)/2, -(title.tamy)/2, 0);
        glTexCoord2f(1,1);  glVertex3f((title.tamx)/2, (title.tamy)/2, 0);
        glTexCoord2f(0,1);  glVertex3f(-(title.tamx)/2, (title.tamy)/2, 0);
      glEnd();
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  for(int x = 0;x<NUM_BOT;x++){
    glPushMatrix();
      glTranslatef(botao[x].posx,botao[x].posy,0);
      glEnable(GL_TEXTURE_2D);
      switch (x) {
        case 2:
          if(op==2){
            glBindTexture(GL_TEXTURE_2D, novojogo2_textura);
          }else{
            glBindTexture(GL_TEXTURE_2D, novojogo_textura);
          }
        break;

        case 1:
        if(op==1){
          glBindTexture(GL_TEXTURE_2D, ajuda2_textura);
        }else{
          glBindTexture(GL_TEXTURE_2D, ajuda_textura);
        }
        break;

        case 0:
        if(op==0){
          glBindTexture(GL_TEXTURE_2D, sair2_textura);
        }else{
          glBindTexture(GL_TEXTURE_2D, sair_textura);
        }
        break;
      }

      glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0,0);  glVertex3f(-(botao[x].tamx)/2, -(botao[x].tamy)/2, 0);
      glTexCoord2f(1,0);  glVertex3f((botao[x].tamx)/2, -(botao[x].tamy)/2, 0);
      glTexCoord2f(1,1);  glVertex3f((botao[x].tamx)/2, (botao[x].tamy)/2, 0);
      glTexCoord2f(0,1);  glVertex3f(-(botao[x].tamx)/2, (botao[x].tamy)/2, 0);
      glEnd();
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }
  }
  glutSwapBuffers();
}

void inicializatextura(){
  glClearColor(0.3,0.3,0.9,0);
  glEnable(GL_BLEND );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  fundao_textura = SOIL_load_OGL_texture("Sem fundo/Fundao.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  novojogo_textura = SOIL_load_OGL_texture("Sem fundo/Novo Jogo.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  novojogo2_textura = SOIL_load_OGL_texture("Sem fundo/Novo Jogo2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  sair_textura = SOIL_load_OGL_texture("Sem fundo/Sair.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  sair2_textura = SOIL_load_OGL_texture("Sem fundo/Sair2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  ajuda_textura = SOIL_load_OGL_texture("Sem fundo/Ajuda.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  title_textura = SOIL_load_OGL_texture("Sem fundo/Title.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  ajuda2_textura = SOIL_load_OGL_texture("Sem fundo/Ajuda2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  peixao_textura = SOIL_load_OGL_texture("Sem fundo/Peixao.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  ajudatela_textura = SOIL_load_OGL_texture("Sem fundo/Ajudaa.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

// Inicia algumas variáveis de estado
void inicializaMenu(void)
{
    egg = 0;
    help = 0;
    ajudaTela.tamx = 450;
    ajudaTela.tamy = 600;
    ajudaTela.posx = 0;
    ajudaTela.posy = 0;
    botao[0].tamx = BOT_LARGURA;
    botao[0].tamy = BOT_ALTURA;
    botao[0].posx = 0;
    botao[0].posy = -250;
    botao[1].tamx = BOT_LARGURA;
    botao[1].tamy = BOT_ALTURA;
    botao[1].posx = 0;
    botao[1].posy = -70;
    botao[2].tamx = BOT_LARGURA;
    botao[2].tamy = BOT_ALTURA;
    botao[2].posx = 0;
    botao[2].posy = 100;
    title.tamx = W;
    title.tamy = BOT_ALTURA+5;
    title.posx = 0;
    title.posy = 245;
    fundao.tamx = W;
    fundao.tamy = H+1000;
    fundao.posx = 0;
    fundao.posy = 0;
    peixao.tamx = 414;
    peixao.tamy = 500;
    peixao.posx = 0;
    peixao.posy = -50;
    inicializatextura();
    // cor para limpar a tela
    glClearColor(1, 1, 1, 0);      // branco
    //criando o anzol
    tocar_musica("Trilhas/Spider.ogg",-1);

}

// Callback de evento de teclado
void tecladoMenu(unsigned char key, int x, int y)
{
    switch(key)
    {
      case 27:
        help = 0;
      break;
    case 'c':
      if(egg == 0){
        egg++;
      }else{
        egg = 0;
      }
    break;
    case 'o':
    if(egg == 7){
      parar_musica();
      tocar_musica("Trilhas/zelda theme.ogg",-1);
    }else{
      if(egg == 1){
        egg++;
      }else{
        egg = 0;
      }
    }
    break;

    case 'u':
    if(egg == 2){
      egg++;
    }else{
      egg = 0;
    }
    break;

    case 't':
    if(egg == 3){
      egg++;
    }else{
      egg = 0;
    }
    break;

    case 'i':
    if(egg == 4){
      egg++;
    }else{
      egg = 0;
    }
    break;

    case 'n':
    if(egg == 5){
      egg++;
    }else{
      egg = 0;
    }
    break;

    case 'h':
    if(egg == 6){
      egg++;
    }else{
      egg = 0;
    }
    break;

    case 'W':
    case 'w':
      if(op==2){
        op =0;
      }else{
        op++;
      }
      egg = 0;
    break;

    case 'S':
        case 's':
        if(op==0){
          op = 2;
        }else{
          op--;
        }
        egg = 0;
    break;

    case 13:
      egg = 0;
      switch (op) {
        case 0:
          exit(0);
        break;

        case 1:
          //ajuda
          help = 1;
        break;

        case 2:
          //iniciar jogo
          parar_musica();
        mainGame();
        break;
      }
    break;
    default:
      egg = 0;
    break;
    }
}

void atualizaMenu(){
  //printf("%i\n",egg);
  //printf("%i\n",op);
  glutPostRedisplay();
  glutTimerFunc(25, atualiza, 0);
}

// Rotina principal
int main(int argc, char **argv)
{

    srand(time(NULL));
    //fundao.posy =
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(W, H);
    // Abre a janela
    glutCreateWindow("Seriously Fishing");
    inicializaMenu();

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaMenu);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(tecladoMenu);
    glutTimerFunc(0, atualizaMenu, 0);
  //

    // Entra em loop e nunca sai
  //  printf("%i\n",egg);
    glutMainLoop();
    return 0;
}
