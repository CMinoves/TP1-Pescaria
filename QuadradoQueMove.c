#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include<time.h>
void desenhaInimigos();
void desenhaPeixe();
int X = 45;
#define LARGURA_DO_MUNDO 100
#define ALTURA_DO_MUNDO 100
#define PEDRA_T 45
#define NUMEROPEDRONA 6
#define NUMEROTILAPA 2
#define VELPEDRAS 7
#define PEIXE_H 40
#define PEIXE_W 60
#define VELPEIXES 5
int keyboard[256];
float aspectratio = 0.7692;
int pause;
int inicio;
int etapa;//0 é descendo, 1 é parada no fundo, 2 é subindo e 3 é parada no topo
typedef struct {
  double posx;
  double posy;
  double tamx;
  double tamy;
  int tipo;
  int dir;
}objeto;
float W = 500;
float H = 650;
objeto coisas[100];
objeto anzol;
objeto fundo;
objeto peixeanzol[99999];
int numpeixes = 0;
objeto pedra[NUMEROPEDRONA];
objeto peixe[NUMEROTILAPA];
void PosColisao(int caso, int ord);
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
  glColor3f(1, 1, 1);
  //desenhando o anzol
  for(int x = 1;x<contobj;x++){
    glPushMatrix();
      glTranslatef(coisas[x].posx,coisas[x].posy,0);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-(coisas[x].tamx)/2, -(coisas[x].tamy)/2, 0);
        glVertex3f((coisas[x].tamx)/2, -(coisas[x].tamy)/2, 0);
        glVertex3f((coisas[x].tamx)/2, (coisas[x].tamy)/2, 0);
        glVertex3f(-(coisas[x].tamx)/2, (coisas[x].tamy)/2, 0);
      glEnd();
      glPopMatrix();
      //desenhando os peixes pegos em cima do anzol
      glPushMatrix();
        glTranslatef(coisas[x].posx,coisas[x].posy-10,0);
      for(int x = 0;x<numpeixes;x++){
        glBegin(GL_TRIANGLE_FAN);

      //  p3------p2
      //  |       |
      //  |       |
      //  p4------p1

      //  p4------p2
      //  |       |
      //  |       |
      //  p1------p1

        glColor3f(0,0,0);
        glVertex3f(-(peixeanzol[x].tamy)/2, -(peixeanzol[x].tamx), 0);//p4
        glColor3f(0,0,0);
        glVertex3f(+(peixeanzol[x].tamy)/2, -(peixeanzol[x].tamx), 0);//p1
        glColor3f(1,1,1);
        glVertex3f((peixeanzol[x].tamy)/2, 0, 0);//p2
        glColor3f(1,1,1);
        glVertex3f(-(peixeanzol[x].tamy)/2, 0, 0);//p3
        glEnd();
      }
    glPopMatrix();
    glColor3f(0, 0, 0);
    desenhaPeixe();
    glColor3f(1,1,0);
    desenhaInimigos();
}
  glutSwapBuffers();
}
int TestaColisoes(objeto colidivel){
  if(coisas[1].posx+coisas[1].tamx/2>=colidivel.posx-colidivel.tamx/2 && coisas[1].posx-coisas[1].tamx/2<=colidivel.posx+colidivel.tamx/2){

   if(coisas[1].posy+coisas[1].tamy/2>=colidivel.posy-colidivel.tamy/2 && coisas[1].posy-coisas[1].tamy/2<=colidivel.posy+colidivel.tamy/2){
    return 1;
   }
  }
	return 0;
}
void DetectaColisoes(){
  //detecta colisões com as predas
  for(int i = 0;i<NUMEROPEDRONA;i++){
    int teste = TestaColisoes(pedra[i]);
    if(teste){
      PosColisao(1,i);
    }
    //detecta colisão com os peixes
    for(int i = 0;i<NUMEROTILAPA;i++){
      int teste = TestaColisoes(peixe[i]);
      if(teste){
        PosColisao(3,i);
      }
      }
  }
}
void inicializaPedras(){
  for(int p = 0; p<NUMEROPEDRONA; p++){
      pedra[p].posy = -H/2 -(rand()%((int)H))-pedra[p].tamy-yfundo;
      pedra[p].posx = -W/2 + (rand()%((int)W));
      pedra[p].tamx = PEDRA_T;
      pedra[p].tamy = PEDRA_T;
      pedra[p].posy+=VELPEDRAS;
  }
}

void desenhaInimigos(){
  for(int p = 0;p<NUMEROPEDRONA;p++){
    glPushMatrix();
    glTranslatef(pedra[p].posx,pedra[p].posy,0);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(-(pedra[p].tamx)/2, -(pedra[p].tamy)/2, 0);
      glVertex3f((pedra[p].tamx)/2, -(pedra[p].tamy)/2, 0);
      glVertex3f((pedra[p].tamx)/2, (pedra[p].tamy)/2, 0);
      glVertex3f(-(pedra[p].tamx)/2, (pedra[p].tamy)/2, 0);
    glEnd();
    glPopMatrix();
  }
}
void desenhaPeixe(){
  for(int p = 0;p<NUMEROTILAPA;p++){
    glPushMatrix();
    glTranslatef(peixe[p].posx,peixe[p].posy,0);
      if(peixe[p].dir){
      glBegin(GL_TRIANGLE_FAN);
        glColor3f(0,0,0);
        glVertex3f(-(peixe[p].tamx)/2, -(peixe[p].tamy)/2, 0);//  p4------p3
        glColor3f(1,1,1);//                                       |       |
        glVertex3f((peixe[p].tamx)/2, -(peixe[p].tamy)/2, 0);//   |       |
        glColor3f(1,1,1);//                                       p1------p2
        glVertex3f((peixe[p].tamx)/2, (peixe[p].tamy)/2, 0);//
        glColor3f(0,0,0);//
        glVertex3f(-(peixe[p].tamx)/2, (peixe[p].tamy)/2, 0);//
      glEnd();//
      glPopMatrix();
    }else{
      glBegin(GL_TRIANGLE_FAN);
        glColor3f(0,0,0);
        glVertex3f((peixe[p].tamx)/2, -(peixe[p].tamy)/2, 0);
        glColor3f(1,1,1);
        glVertex3f(-(peixe[p].tamx)/2, -(peixe[p].tamy)/2, 0);
        glColor3f(1,1,1);//
        glVertex3f(-(peixe[p].tamx)/2, (peixe[p].tamy)/2, 0);//
        glColor3f(0,0,0);//
        glVertex3f((peixe[p].tamx)/2, (peixe[p].tamy)/2, 0);//
      glEnd();
      glPopMatrix();
    }
  }
}
void inicializaPeixe(){

  for(int p = 0;p<NUMEROTILAPA;p++){
    peixe[p].posx = -W/2 + (rand()%((int)W));
    peixe[p].posy = -H/2 +(rand()%((int)H))-peixe[p].tamy-yfundo-H;
    peixe[p].tamx = PEIXE_W;
    peixe[p].tamy = PEIXE_H;
    peixe[p].dir = rand()%2;
    //direita = 1 e esquerda = 0
   }
}
// Inicia algumas variáveis de estado
void inicializa(void)
{
    // cor para limpar a tela
    glClearColor(1, 1, 1, 0);      // branco
    //criando o anzol
    anzol.posx = 0;
    anzol.posy = 200;
    anzol.tamx = 30;
    anzol.tamy = 30;
    anzol.tipo = 0;
    coisas[1] = anzol;
    contobj ++;
    //criando o fundo
    fundo.posx = 0;
    fundo.posy = 0;
    fundo.tamx = W;
    fundo.tamy = 5000;
    fundo.tipo = 1;
    coisas[0] = fundo;
    inicializaPedras();
    inicializaPeixe();
    pause = 0;
    inicio = 1;
    etapa = 0;
}

// Callback de redimensionamento
void redimensiona(int w, int h)
{
    //   W = w;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -1, 1);
    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  //  coisas[0].tamx = w;
  //  int w2 = h*aspectratio;
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

    case 'p':
      case 'P':
        if(!inicio){
          if(pause){
            pause = 0;
          }else{
            pause = 1;
          }
        }
      break;
    case 13:
      if(inicio){
        inicio = 0;
        pause = 1;
      }
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
void PosColisao(int caso, int ord){
  switch (etapa){
    case 0:
      switch (caso){
        case 1: //colisão com pedras
          pedra[ord].posy = -H/2 -(rand()%((int)H))-pedra[ord].tamy-yfundo;
          pedra[ord].posx = -W/2 + (rand()%((int)W));
        break;
        case 2: //colisão com power ups de vida

        break;
        case 3: //colisao com peixe
          peixeanzol[numpeixes] = peixe[ord];
          numpeixes ++;
          peixe[ord].posy = -H/2 -(rand()%((int)H))-peixe[ord].tamy-yfundo;
          peixe[ord].posx = -W/2 + (rand()%((int)W));
        break;
      }
    break;
    case 1:

    break;
  }
}

void atualizaobjetos(int i, int tipo){
  switch (tipo) {
    case 0 : //anzol
    if(keyboard['a'] && coisas[1].posx>-(W/2-(coisas[1].tamx/2)-10)){
      coisas[1].posx-=10;
    }
    if(keyboard['d'] && coisas[1].posx<(W/2-(coisas[1].tamx/2))-10){
      coisas[1].posx+=10;
    }
    break;

    case 1: //pedra
    pedra[i].posy = -H/2 -(rand()%((int)H))-pedra[i].tamy-yfundo;
    pedra[i].posx = -W/2 + (rand()%((int)W));
    break;

    case 2: //ṕeixe
    peixe[i].posy = -H/2 -(rand()%((int)H))-peixe[i].tamy-yfundo;
    peixe[i].posx = -W/2 + (rand()%((int)W));
    break;
  }

}
void atualiza(){
  if(!pause){
    if(inicio){
      //escrever o que está no printf na tela
      printf("Pressione enter para iniciar!\n");
    }
    printf("%i\n",inicio );
  }else{
      //movimento do anzol
  atualizaobjetos(1,0);

  //desenha o anzol
//  printf("%f\n",coisas[1].posx);
    switch (etapa){
      case 0:
        //descendo para o fundo
        yfundo +=0.4;
        for(int p = 0; p<NUMEROPEDRONA; p++){
          if(pedra[p].posy>(H/2+(pedra[p].tamy))){
            atualizaobjetos(p,1);
          }
          pedra[p].posy+=VELPEDRAS;
        }
        //atualização dos peixes
        for(int p = 0; p<NUMEROTILAPA; p++){
          if(peixe[p].posy>(H/2+(peixe[p].tamy))){
            atualizaobjetos(p,2);
          }
          peixe[p].posy+=VELPEDRAS;

        }
      break;
      case 1:
        //parado no fundo e anzol descendo
      break;
      case 2:
        yfundo -= 0.4;
        //subindo ao topo
      break;
      case 3:
        //parado e anzol subindo
      break;
      default:

      break;


  //atualiza pedras

  //faz o peixe ir e voltar no eixo x
    }
    for(int p = 0; p<NUMEROTILAPA; p++){
      if(peixe[p].dir){
        if(peixe[p].posx+peixe[p].tamx/2 >=W/2){
          peixe[p].dir = 0;
          peixe[p].posx = W/2-PEIXE_W/2;
        }else{
          peixe[p].posx +=VELPEIXES;
        }
      }else{
        if(peixe[p].posx-peixe[p].tamx/2 <=-W/2){
          peixe[p].dir = 1;
          peixe[p].posx = -W/2+PEIXE_W/2;
        }else{
          peixe[p].posx -=VELPEIXES;
        }
      }
    }
  //  desenhaCena();
  //  glutSwapBuffers();
    }
  DetectaColisoes();
  glutPostRedisplay();
  glutTimerFunc(25, atualiza, 0);
}
// Rotina principal
int main(int argc, char **argv)
{

    srand(time(NULL));
    //fundo.posy =
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(W, H);
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
