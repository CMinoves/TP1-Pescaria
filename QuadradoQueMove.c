#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include<time.h>
#include<SOIL/SOIL.h>
#include<math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

void parar_musica();
void desenhaInimigos();
void desenhaPeixe();
void desenhaVidinha();
void EtapasdoGame();
void atualizaobjetos(int i, int tipo, int colidi);
void desenhahud();
void inicializahud();
void DesenhaPause();
void inicializapowerUpVidinha();
void DesenhaGameOver();

GLuint anzol_textura;
GLuint um_textura;
GLuint dois_textura;
GLuint tres_textura;
GLuint quatro_textura;
GLuint cinco_textura;
GLuint seis_textura;
GLuint sete_textura;
GLuint oito_textura;
GLuint nove_textura;
GLuint zero_textura;
GLuint fundo_textura;
GLuint gameover_textura;
GLuint hud0_textura;
GLuint hud1_textura;
GLuint hud2_textura;
GLuint hud3_textura;
GLuint pause_textura;
GLuint iniciar_textura;
GLuint peixe1_textura;
GLuint peixe2_textura;
GLuint preda_textura;
GLuint score_textura;
GLuint submarino_textura;
GLuint tubarao_textura;
GLuint blank_textura;
GLuint vidinha_textura;

int X = 45;
float animapeixe;
int endsong;
int dificuldade;
#define LARGURA_DO_MUNDO 100
#define ALTURA_DO_MUNDO 100
#define PEDRA_T 50
#define NUMEROPEDRONA 6
#define NUMEROTILAPA 2
#define VELPEDRAS 9
#define VELVIDINHA 10
#define PEIXE_H 40
#define PEIXE_W 60
#define VELPEIXES 8
int keyboard[256];
float aspectratio = 0.7692;
int pause;
int auxiliar;
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
objeto vidinha;
void PosColisao(int caso, int ord);
objeto vida;
objeto score;
objeto profu;
objeto profd;
objeto profc;
objeto scorem;
objeto scorec;
objeto scored;
objeto scoreu;
objeto pausegame;
objeto gameover;
int pontos = 0;
//coisas[1] = fundo;
int contobj = 1;
int hp;
float yfundo = 0;

void tocar_musica(char const nome[40], int loop){
        Mix_Chunk *som = NULL;
        int canal;
   int canal_audio=2;
        int taxa_audio = 22050;
        Uint16 formato_audio = AUDIO_S16SYS;
        int audio_buffers = 4096;
        if(Mix_OpenAudio(taxa_audio, formato_audio, canal_audio, audio_buffers) != 0) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
       som = Mix_LoadWAV(nome);
        if(som == NULL) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
       Mix_HaltChannel(-1);
       canal = Mix_PlayChannel( -1, som, loop);
        if(canal == -1) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
}

void parar_musica(){
 Mix_HaltChannel(-1);
}


void CarregaTexturas(){
  glClearColor(0.3,0.3,0.9,0);
  glEnable(GL_BLEND);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  score_textura = SOIL_load_OGL_texture("Sem fundo/Score.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  fundo_textura = SOIL_load_OGL_texture("Sem fundo/Fundo.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  anzol_textura = SOIL_load_OGL_texture("Sem fundo/Anzol2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  um_textura = SOIL_load_OGL_texture("Sem fundo/Um.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  dois_textura = SOIL_load_OGL_texture("Sem fundo/Dois.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  tres_textura = SOIL_load_OGL_texture("Sem fundo/Tres.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  quatro_textura = SOIL_load_OGL_texture("Sem fundo/Quatro.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  cinco_textura = SOIL_load_OGL_texture("Sem fundo/Cinco.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  seis_textura = SOIL_load_OGL_texture("Sem fundo/Seis.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  sete_textura = SOIL_load_OGL_texture("Sem fundo/Sete.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  oito_textura = SOIL_load_OGL_texture("Sem fundo/Oito.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  nove_textura = SOIL_load_OGL_texture("Sem fundo/Nove.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  zero_textura = SOIL_load_OGL_texture("Sem fundo/Zero.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  gameover_textura = SOIL_load_OGL_texture("Sem fundo/Game Over.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  hud0_textura = SOIL_load_OGL_texture("Sem fundo/HUD0.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  hud1_textura = SOIL_load_OGL_texture("Sem fundo/HUD1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  hud2_textura = SOIL_load_OGL_texture("Sem fundo/HUD2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  hud3_textura = SOIL_load_OGL_texture("Sem fundo/HUD3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  pause_textura = SOIL_load_OGL_texture("Sem fundo/Pause.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  iniciar_textura = SOIL_load_OGL_texture("Sem fundo/Iniciar.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  peixe1_textura = SOIL_load_OGL_texture("Sem fundo/Peixe01.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  peixe2_textura = SOIL_load_OGL_texture("Sem fundo/Peixe03.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  preda_textura = SOIL_load_OGL_texture("Sem fundo/Preda.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  submarino_textura = SOIL_load_OGL_texture("Sem fundo/Submarino.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  tubarao_textura = SOIL_load_OGL_texture("Sem fundo/Tubarao.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  vidinha_textura = SOIL_load_OGL_texture("Sem fundo/Vida.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  if(score_textura==0){
    printf("Deu ruim!\n");
  }
}

void desenhaQuadrado(void){
  glColor3f(1,1,1);
  glClear(GL_COLOR_BUFFER_BIT);
  //desenhando o fundo cabuloso
    glPushMatrix();
      glTranslatef(0,yfundo,0);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, fundo_textura);
      glBegin(GL_POLYGON);
        glTexCoord2f(0,0);  glVertex3f(-(fundo.tamx)/2, -(fundo.tamy)/2, 0);
        glTexCoord2f(1,0);  glVertex3f((fundo.tamx)/2, -(fundo.tamy)/2, 0);
        glTexCoord2f(1,1);  glVertex3f((fundo.tamx)/2, (fundo.tamy)/2, 0);
        glTexCoord2f(0,1);  glVertex3f(-(fundo.tamx)/2, (fundo.tamy)/2, 0);
      glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  //fim do desenho do fundo

  //desenhando o anzol
    glColor3f(1,1,1);
    glPushMatrix();
      glTranslatef(anzol.posx,anzol.posy,0);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, anzol_textura);
      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);  glVertex3f(-(anzol.tamx)/2, -(anzol.tamy)/2, 0);
        glTexCoord2f(1,0);  glVertex3f((anzol.tamx)/2, -(anzol.tamy)/2, 0);
        glTexCoord2f(1,1);  glVertex3f((anzol.tamx)/2, (anzol.tamy)/2, 0);
        glTexCoord2f(0,1);  glVertex3f(-(anzol.tamx)/2, (anzol.tamy)/2, 0);
      glEnd();
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      //desenhando o último peixe pego em cima do anzol
      glPushMatrix();
        glTranslatef(anzol.posx,anzol.posy-10,0);
        glEnable(GL_TEXTURE_2D);
        if(peixeanzol[numpeixes-1].tipo == 1){
          glBindTexture(GL_TEXTURE_2D, peixe1_textura);
        }else{
          glBindTexture(GL_TEXTURE_2D, peixe2_textura);
        }
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,1);  glVertex3f(-(peixeanzol[numpeixes-1].tamy)/2, -(peixeanzol[numpeixes-1].tamx), 0);//p4
        glTexCoord2f(0,0);  glVertex3f((peixeanzol[numpeixes-1].tamy)/2, -(peixeanzol[numpeixes-1].tamx), 0);//p1
        glTexCoord2f(0.125,0);  glVertex3f((peixeanzol[numpeixes-1].tamy)/2, 0, 0);//p2
        glTexCoord2f(0.125,1);  glVertex3f(-(peixeanzol[numpeixes-1].tamy)/2, 0, 0);//p3
        glEnd();
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    desenhaPeixe();
    desenhaInimigos();
    desenhaVidinha();
    desenhahud();
    if(!pause){
      DesenhaPause();
    }
    if (hp==0){
      DesenhaGameOver();
      if(endsong == 0){
        parar_musica();
        tocar_musica("Trilhass/Game_over.ogg",1);
        endsong = 1;
      }
    }
    glutSwapBuffers();
}
void inicializahud(){
  hp = 3;
  vida.tamx = 124;
  vida.tamy = 100;
  vida.posx = -W/2+vida.tamx/2;
  vida.posy = H/2-vida.tamy/2;
  score.tamx = 154;
  score.tamy = 86;
  score.posx = W/2-score.tamx/2;
  score.posy = H/2-score.tamy/2;

  profc.tamx = 20;
  profc.tamy = 34;
  profc.posx = -200-profc.tamx-10;
  profc.posy = 300-profc.tamy-13;

  profu.tamx = 20;
  profu.tamy = 34;
  profu.posx = -150-profc.tamx-10;
  profu.posy = profc.posy;

  profd.tamx = 20;
  profd.tamy = 34;
  profd.posx = -185-profc.tamx;
  profd.posy = 300-profc.tamy-13;




  scoreu.tamx = 20;
  scoreu.tamy = 34;
  scoreu.posx = 210;
  scoreu.posy = 265;

  scored.tamx = 20;
  scored.tamy = 34;
  scored.posx = 180;
  scored.posy = 265;

  scorec.tamx = 20;
  scorec.tamy = 34;
  scorec.posx = 150;
  scorec.posy = 265;

  scorem.tamx = 20;
  scorem.tamy = 34;
  scorem.posx = 120;
  scorem.posy = 265;
}

void desfinealgarismo(int num){
  switch (num) {
    case 0:
      glBindTexture(GL_TEXTURE_2D, zero_textura);
    break;

    case 1:
      glBindTexture(GL_TEXTURE_2D, um_textura);
    break;

    case 2:
      glBindTexture(GL_TEXTURE_2D, dois_textura);
    break;

    case 3:
      glBindTexture(GL_TEXTURE_2D, tres_textura);
    break;

    case 4:
      glBindTexture(GL_TEXTURE_2D, quatro_textura);
    break;

    case 5:
      glBindTexture(GL_TEXTURE_2D, cinco_textura);
    break;

    case 6:
      glBindTexture(GL_TEXTURE_2D, seis_textura);
    break;

    case 7:
      glBindTexture(GL_TEXTURE_2D, sete_textura);
    break;

    case 8:
      glBindTexture(GL_TEXTURE_2D, oito_textura);
    break;

    case 9:
      glBindTexture(GL_TEXTURE_2D, nove_textura);
    break;

    default:

    break;
  }
}
void desenhahud(){
  int numaux;
  int prof = (int)yfundo/2;
  //desenha o hud de vida
  glPushMatrix();
    glTranslatef(vida.posx,vida.posy,0);
    glEnable(GL_TEXTURE_2D);
    switch(hp){
      case 3:
        glBindTexture(GL_TEXTURE_2D, hud3_textura);
      break;

      case 2:
        glBindTexture(GL_TEXTURE_2D, hud2_textura);
      break;

      case 1:
        glBindTexture(GL_TEXTURE_2D, hud1_textura);
      break;

      case 0:
        glBindTexture(GL_TEXTURE_2D, hud0_textura);
      break;

      default:
        glBindTexture(GL_TEXTURE_2D, blank_textura);
      break;
    }

    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0,0);  glVertex3f(-(vida.tamx)/2, -(vida.tamy)/2, 0);
      glTexCoord2f(1,0);  glVertex3f((vida.tamx)/2, -(vida.tamy)/2, 0);
      glTexCoord2f(1,1);  glVertex3f((vida.tamx)/2, (vida.tamy)/2, 0);
      glTexCoord2f(0,1);  glVertex3f(-(vida.tamx)/2, (vida.tamy)/2, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //desenhando os números da profundidade
    glPushMatrix();
      glTranslatef(profc.posx,profc.posy,0);
      glEnable(GL_TEXTURE_2D);
      numaux = prof/100;
      desfinealgarismo(numaux);
      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);  glVertex3f(-(profc.tamx)/2, -(profc.tamy)/2, 0);
        glTexCoord2f(1,0);  glVertex3f((profc.tamx)/2, -(profc.tamy)/2, 0);
        glTexCoord2f(1,1);  glVertex3f((profc.tamx)/2, (profc.tamy)/2, 0);
        glTexCoord2f(0,1);  glVertex3f(-(profc.tamx)/2, (profc.tamy)/2, 0);
      glEnd();
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(profd.posx,profd.posy,0);
        glEnable(GL_TEXTURE_2D);
        numaux = (prof/10)%10;
        desfinealgarismo(numaux);
        glBegin(GL_TRIANGLE_FAN);
          glTexCoord2f(0,0);  glVertex3f(-(profd.tamx)/2, -(profd.tamy)/2, 0);
          glTexCoord2f(1,0);  glVertex3f((profd.tamx)/2, -(profd.tamy)/2, 0);
          glTexCoord2f(1,1);  glVertex3f((profd.tamx)/2, (profd.tamy)/2, 0);
          glTexCoord2f(0,1);  glVertex3f(-(profd.tamx)/2, (profd.tamy)/2, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
          glTranslatef(profu.posx,profu.posy,0);
          glEnable(GL_TEXTURE_2D);
          numaux = prof%10;
          desfinealgarismo(numaux);
          glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0,0);  glVertex3f(-(profu.tamx)/2, -(profu.tamy)/2, 0);
            glTexCoord2f(1,0);  glVertex3f((profu.tamx)/2, -(profu.tamy)/2, 0);
            glTexCoord2f(1,1);  glVertex3f((profu.tamx)/2, (profu.tamy)/2, 0);
            glTexCoord2f(0,1);  glVertex3f(-(profu.tamx)/2, (profu.tamy)/2, 0);
          glEnd();
          glDisable(GL_TEXTURE_2D);
          glPopMatrix();
        //desenhando a tabela de score
    glPushMatrix();
      glTranslatef(score.posx,score.posy,0);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, score_textura);
      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);  glVertex3f(-(score.tamx)/2, -(score.tamy)/2, 0);
        glTexCoord2f(1,0);  glVertex3f((score.tamx)/2, -(score.tamy)/2, 0);
        glTexCoord2f(1,1);  glVertex3f((score.tamx)/2, (score.tamy)/2, 0);
        glTexCoord2f(0,1);  glVertex3f(-(score.tamx)/2, (score.tamy)/2, 0);
      glEnd();
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      //desenhando os números do score
      glPushMatrix();
        glTranslatef(scorem.posx,scorem.posy,0);
        glEnable(GL_TEXTURE_2D);
        numaux = pontos/1000;
        desfinealgarismo(numaux);
        glBegin(GL_TRIANGLE_FAN);
          glTexCoord2f(0,0);  glVertex3f(-(scorem.tamx)/2, -(scorem.tamy)/2, 0);
          glTexCoord2f(1,0);  glVertex3f((scorem.tamx)/2, -(scorem.tamy)/2, 0);
          glTexCoord2f(1,1);  glVertex3f((scorem.tamx)/2, (scorem.tamy)/2, 0);
          glTexCoord2f(0,1);  glVertex3f(-(scorem.tamx)/2, (scorem.tamy)/2, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
          glTranslatef(scorec.posx,scorec.posy,0);
          glEnable(GL_TEXTURE_2D);
          numaux = (pontos/100)%10;
          desfinealgarismo(numaux);
          glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0,0);  glVertex3f(-(scorec.tamx)/2, -(scorec.tamy)/2, 0);
            glTexCoord2f(1,0);  glVertex3f((scorec.tamx)/2, -(scorec.tamy)/2, 0);
            glTexCoord2f(1,1);  glVertex3f((scorec.tamx)/2, (scorec.tamy)/2, 0);
            glTexCoord2f(0,1);  glVertex3f(-(scorec.tamx)/2, (scorec.tamy)/2, 0);
          glEnd();
          glDisable(GL_TEXTURE_2D);
          glPopMatrix();

          glPushMatrix();
            glTranslatef(scored.posx,scored.posy,0);
            glEnable(GL_TEXTURE_2D);
            numaux = (pontos/10)%100;
            desfinealgarismo(numaux);
            glBegin(GL_TRIANGLE_FAN);
              glTexCoord2f(0,0);  glVertex3f(-(scored.tamx)/2, -(scored.tamy)/2, 0);
              glTexCoord2f(1,0);  glVertex3f((scored.tamx)/2, -(scored.tamy)/2, 0);
              glTexCoord2f(1,1);  glVertex3f((scored.tamx)/2, (scored.tamy)/2, 0);
              glTexCoord2f(0,1);  glVertex3f(-(scored.tamx)/2, (scored.tamy)/2, 0);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();

            glPushMatrix();
              glTranslatef(scoreu.posx,scoreu.posy,0);
              glEnable(GL_TEXTURE_2D);
              numaux = pontos%10;
              desfinealgarismo(numaux);
              glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0,0);  glVertex3f(-(scoreu.tamx)/2, -(scoreu.tamy)/2, 0);
                glTexCoord2f(1,0);  glVertex3f((scoreu.tamx)/2, -(scoreu.tamy)/2, 0);
                glTexCoord2f(1,1);  glVertex3f((scoreu.tamx)/2, (scoreu.tamy)/2, 0);
                glTexCoord2f(0,1);  glVertex3f(-(scoreu.tamx)/2, (scoreu.tamy)/2, 0);
              glEnd();
              glDisable(GL_TEXTURE_2D);
              glPopMatrix();




}

int TestaColisoes(objeto colidivel){
  if(anzol.posx+anzol.tamx/2>=colidivel.posx-colidivel.tamx/2 && anzol.posx-anzol.tamx/2<=colidivel.posx+colidivel.tamx/2){

   if(anzol.posy+anzol.tamy/2>=colidivel.posy-colidivel.tamy/2 && anzol.posy-anzol.tamy/2<=colidivel.posy+colidivel.tamy/2){
    return 1;
   }
  }
	return 0;
}

void DesenhaPause(){
  pausegame.posx = 0;
  pausegame.posy = 0;
  pausegame.tamx = 268;
  pausegame.tamy = 52;

  glPushMatrix();
    glTranslatef(pausegame.posx,pausegame.posy,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, pause_textura);
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0,0);  glVertex3f(-(pausegame.tamx)/2, -(pausegame.tamy)/2, 0);
      glTexCoord2f(1,0);  glVertex3f((pausegame.tamx)/2, -(pausegame.tamy)/2, 0);
      glTexCoord2f(1,1);  glVertex3f((pausegame.tamx)/2, (pausegame.tamy)/2, 0);
      glTexCoord2f(0,1);  glVertex3f(-(pausegame.tamx)/2, (pausegame.tamy)/2, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void DesenhaGameOver(){
  gameover.posx = 0;
  gameover.posy = 0;
  gameover.tamx = 268;
  gameover.tamy = 52;

  glPushMatrix();
    glTranslatef(gameover.posx,gameover.posy,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gameover_textura);
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0,0);  glVertex3f(-(gameover.tamx)/2, -(gameover.tamy)/2, 0);
      glTexCoord2f(1,0);  glVertex3f((gameover.tamx)/2, -(gameover.tamy)/2, 0);
      glTexCoord2f(1,1);  glVertex3f((gameover.tamx)/2, (gameover.tamy)/2, 0);
      glTexCoord2f(0,1);  glVertex3f(-(gameover.tamx)/2, (gameover.tamy)/2, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void DetectaColisoes(){
  //detecta colisões com as predas
  for(int i = 0;i<NUMEROPEDRONA;i++){
    int teste = TestaColisoes(pedra[i]);
    if(teste){
      PosColisao(1,i);
    }
  }
    //detecta colisão com os peixes
  for(int i = 0;i<NUMEROTILAPA;i++){
    int teste = TestaColisoes(peixe[i]);
      if(teste){
        PosColisao(3,i);
      }
  }

    //detecta colisão com a vidinha
  int teste = TestaColisoes(vidinha);
  if (teste){
    PosColisao(2,0);
  }
}
void inicializaPedras(){
  for(int p = 0; p<NUMEROPEDRONA; p++){
      pedra[p].posy = -H/2 -(rand()%((int)H))-pedra[p].tamy-yfundo;
      pedra[p].posx = -W/2 + (rand()%((int)W));
      pedra[p].tamx = PEDRA_T;
      pedra[p].tamy = PEDRA_T;
      pedra[p].posy = pedra[p].posy +(VELPEDRAS+dificuldade);
  }
}
//asdfg
void inicializapowerUpVidinha(){
    vidinha.posy = -rand()%3000-H/2;
    vidinha.posx = -W/2 + (rand()%((int)W));
    vidinha.tamx = 30;
    vidinha.tamy = 30;
    vidinha.posy= vidinha.posy+(VELVIDINHA+dificuldade);
    vidinha.tipo = 1;
}
void desenhaInimigos(){
  for(int p = 0;p<NUMEROPEDRONA;p++){
    glPushMatrix();
    glTranslatef(pedra[p].posx,pedra[p].posy,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, preda_textura);
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0,0);  glVertex3f(-(pedra[p].tamx)/2, -(pedra[p].tamy)/2, 0);
      glTexCoord2f(1,0);  glVertex3f((pedra[p].tamx)/2, -(pedra[p].tamy)/2, 0);
      glTexCoord2f(1,1);  glVertex3f((pedra[p].tamx)/2, (pedra[p].tamy)/2, 0);
      glTexCoord2f(0,1);  glVertex3f(-(pedra[p].tamx)/2, (pedra[p].tamy)/2, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }
}
void desenhaPeixe(){
  for(int p = 0;p<NUMEROTILAPA;p++){
    glPushMatrix();
    glTranslatef(peixe[p].posx,peixe[p].posy,0);
    glEnable(GL_TEXTURE_2D);
    if(peixe[p].tipo == 1){
      glBindTexture(GL_TEXTURE_2D, peixe1_textura);
    }else{
      glBindTexture(GL_TEXTURE_2D, peixe2_textura);
    }
      if(peixe[p].dir == 1){
      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f((animapeixe-1)/8,0);  glVertex3f(-(peixe[p].tamx)/2, -(peixe[p].tamy)/2, 0);//
        glTexCoord2f(animapeixe/8,0);  glVertex3f((peixe[p].tamx)/2, -(peixe[p].tamy)/2, 0);//
        glTexCoord2f(animapeixe/8,1);  glVertex3f((peixe[p].tamx)/2, (peixe[p].tamy)/2, 0);//
        glTexCoord2f((animapeixe-1)/8,1);  glVertex3f(-(peixe[p].tamx)/2, (peixe[p].tamy)/2, 0);//
      glEnd();//
      glPopMatrix();
    }else{
      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f((animapeixe-1)/8,0); glVertex3f((peixe[p].tamx)/2, -(peixe[p].tamy)/2, 0);
        glTexCoord2f(animapeixe/8,0); glVertex3f(-(peixe[p].tamx)/2, -(peixe[p].tamy)/2, 0);
        glTexCoord2f(animapeixe/8,1); glVertex3f(-(peixe[p].tamx)/2, (peixe[p].tamy)/2, 0);//
        glTexCoord2f((animapeixe-1)/8,1); glVertex3f((peixe[p].tamx)/2, (peixe[p].tamy)/2, 0);//
      glEnd();
      glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
  }
}
void desenhaVidinha(){
  if(vidinha.tipo == 1){
  glPushMatrix();
    glTranslatef(vidinha.posx,vidinha.posy,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, vidinha_textura);
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0,0); glVertex3f(-(vidinha.tamx)/2, -(vidinha.tamy)/2,0);
      glTexCoord2f(1,0); glVertex3f((vidinha.tamx)/2, -(vidinha.tamy)/2,0);
      glTexCoord2f(1,1); glVertex3f((vidinha.tamx)/2, (vidinha.tamy)/2,0);
      glTexCoord2f(0,1); glVertex3f(-(vidinha.tamx)/2, (vidinha.tamy)/2,0);
    glEnd();
  glPopMatrix();
  }
}
void inicializaPeixe(){
  for(int p = 0;p<NUMEROTILAPA;p++){
    peixe[p].posx = -W/2 + (rand()%((int)W));
    peixe[p].posy = -H/2 +(rand()%((int)H))-peixe[p].tamy-yfundo-H;
    peixe[p].tamx = PEIXE_W;
    peixe[p].tamy = PEIXE_H;
    peixe[p].dir = 1;
    //direita = 1 e esquerda = 0
    auxiliar = rand()%100;
    if(auxiliar<=20+dificuldade){
      peixe[p].tipo = 2;
    }else{
      peixe[p].tipo = 1;
    }

   }
}
// Inicia algumas variáveis de estado
void inicializa(void){
    dificuldade = -1;
    CarregaTexturas();
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
    fundo.tamy = 2000+H/2+500;
    fundo.tipo = 1;
    coisas[0] = fundo;
    inicializahud();
    inicializaPedras();
    inicializaPeixe();
    inicializapowerUpVidinha();
    pause = 0;
    inicio = 1;
    etapa = 0;
    yfundo = 0;
    hp = 3;
    endsong = 0;
    animapeixe = 1;

    parar_musica();
    tocar_musica("Trilhass/Crash_song.ogg",-1);
}

// Callback de redimensionamento
void redimensiona(int w, int h){

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
        if(!pause)
          exit(0);
        break;
    case 'r':
      numpeixes = 0;
      pontos = 0;
      inicializa();
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
        if(hp!=0){
        if(!inicio){
          if(pause){

            pause = 0;
            parar_musica();
            tocar_musica("Trilhass/Pause_beat.ogg",-1);
          }else{
            pause = 1;
            parar_musica();
            tocar_musica("Trilhass/Crash_song.ogg",-1);
          }
        }
      }
      break;
    case 13:
      if(inicio){
        inicio = 0;
        pause = 1;
      }
      if(hp==0){
        exit(0);
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
    if(etapa%2 ==0){
      switch (caso){
        case 1: //colisão com pedras
          atualizaobjetos(ord, 1, 1);
            hp --;
          //pedra[ord].posy = -H/2 -(rand()%((int)H))-pedra[ord].tamy-yfundo;
      //    pedra[ord].posx = -W/2 + (rand()%((int)W));
        break;
        case 2: //colisão com power ups de vidinha
          if(hp!=3){
            hp++;
            vidinha.tipo = 0;
          }
        break;
        case 3: //colisao com peixe
          peixeanzol[numpeixes] = peixe[ord];
          numpeixes ++;
          atualizaobjetos(ord, 2, 1);
        //  peixe[ord].posy = -H/2 -(rand()%((int)H))-peixe[ord].tamy-yfundo;
        //  peixe[ord].posx = -W/2 + (rand()%((int)W));
        break;
      }
    }else{
      switch (caso){
        case 1: //colisão com pedras
          atualizaobjetos(ord, 1, 1);

          if(hp == 0){
            hp = 3;
          }else{
            hp --;
          }
          //pedra[ord].posy = -H/2 -(rand()%((int)H))-pedra[ord].tamy-yfundo;
      //    pedra[ord].posx = -W/2 + (rand()%((int)W));
        break;
        case 2: //colisão com power ups de vidinha
          if(hp!=3){
            hp++;
            vidinha.tipo = 0;
          }
        break;
        case 3: //colisao com peixe
          peixeanzol[numpeixes] = peixe[ord];
          numpeixes ++;
          atualizaobjetos(ord, 2, 1);
        //  peixe[ord].posy = -H/2 -(rand()%((int)H))-peixe[ord].tamy-yfundo;
        //  peixe[ord].posx = -W/2 + (rand()%((int)W));
        break;
  }
}
}
void atualizaobjetos(int i, int tipo, int colidi){
  switch (tipo) {
    case 0 : //anzol
    if(keyboard['a'] && anzol.posx>-(W/2-(anzol.tamx/2)-10)){
      anzol.posx-=10;
    }
    if(keyboard['d'] && anzol.posx<(W/2-(anzol.tamx/2))-10){
      anzol.posx+=10;
    }
    switch (etapa) {
      case 1:
        anzol.posy -=10;
      break;

      case 3:
        anzol.posy+=10;
      break;

      default:

      break;
    }
    break;

    case 1: //pedra

    switch (etapa) {
      case 1:
      case 0:
        if(pedra[i].posy>(H/2+(pedra[i].tamy))|| colidi){
          pedra[i].posy = -H/2 -(rand()%((int)H))-pedra[i].tamy-yfundo;
          pedra[i].posx = -W/2 + (rand()%((int)W));
        }
        pedra[i].posy= pedra[i].posy+(VELPEDRAS+dificuldade);
      break;

      case 2:
      case 3:
      if(pedra[i].posy<(-H/2-(pedra[i].tamy))||colidi){
        pedra[i].posy = +H/2 +(rand()%((int)H))+pedra[i].tamy;
        pedra[i].posx = -W/2 + (rand()%((int)W));
      }
      pedra[i].posy = pedra[i].posy-(VELPEDRAS+dificuldade);
      break;

      default:

      break;
    }
    break;

    case 2: //peixe
    switch (etapa) {
      case 0:
      case 1:
        if(peixe[i].posy>(H/2-(peixe[i].tamy))||colidi){
          peixe[i].posy = -H/2 -(rand()%((int)H))-peixe[i].tamy-yfundo;
          peixe[i].posx = -W/2 + (rand()%((int)W));
        auxiliar = rand()%100;
        if(auxiliar<=30+dificuldade){
          peixe[i].tipo = 2;
        }else{
          peixe[i].tipo = 1;
        }
        }
        peixe[i].posy = peixe[i].posy +(VELPEIXES+dificuldade);
      break;

      case 2:
      case 3:
      if(peixe[i].posy<(-H/2-(peixe[i].tamy))||colidi){
        peixe[i].posy = +H/2 +(rand()%((int)H))+peixe[i].tamy;
        peixe[i].posx = -W/2 + (rand()%((int)W));
        auxiliar = rand()%100;
        if(auxiliar<=30+dificuldade){
          peixe[i].tipo = 2;
        }else{
          peixe[i].tipo = 1;
        }
      }
      peixe[i].posy=peixe[i].posy-(VELPEIXES+dificuldade);
      break;
//    peixe[i].posy = -H/2 -(rand()%((int)H))-peixe[i].tamy-yfundo;
  //  peixe[i].posx = -W/2 + (rand()%((int)W));
      default:

      break;
    }
  }
}
void ContarPontos(){
  for(int x = 0; x<numpeixes;x++){
    if(peixeanzol[x].tipo == 1){
      pontos+=40;
    }else{
      pontos+=20;
    }
  }
}
void EtapasdoGame(){
    if(yfundo == 0 && anzol.posy >= 200){
      if(inicio != 1){
      etapa = 0;
      ContarPontos();
      peixeanzol[0].tamx = 0;
      peixeanzol[0].tamy = 0;
      numpeixes = 0;
      if(dificuldade<10){
        dificuldade ++;
      }
    }
    }
    if(yfundo >= 1000 && anzol.posy == 200){
      etapa = 1;
    }
    if(yfundo >= 1000 && anzol.posy == -200){
      etapa = 2;
    }
    if(yfundo <= 0 && anzol.posy ==-200){
      etapa = 3;
    }
}

void atualiza(){
  if(!pause||hp==0){
    if(inicio){
      //escrever o que está no printf na tela
  //    printf("Pressione enter para iniciar!\n");
    }
    //printf("%i\n",inicio );
  }else{

    if(animapeixe == 8){
      animapeixe = 1;
    }else{
      animapeixe ++;
    }
      //movimento do anzol
  atualizaobjetos(1,0,0);
        //descendo para o fundo

        for(int p = 0; p<NUMEROPEDRONA; p++){
            atualizaobjetos(p,1,0);
          }
        //atualização dos peixes
        for(int p = 0; p<NUMEROTILAPA; p++){
            atualizaobjetos(p,2,0);
        }
        for(int p = 0; p<NUMEROTILAPA; p++){
            if(peixe[p].dir){
        if(peixe[p].posx+peixe[p].tamx/2 >=W/2){
          peixe[p].dir = 0;
          peixe[p].posx = W/2-PEIXE_W/2;
        }else{
          peixe[p].posx +=(VELPEIXES);
        }
      }else{
        if(peixe[p].posx-peixe[p].tamx/2 <=-W/2){
          peixe[p].dir = 1;
          peixe[p].posx = -W/2+PEIXE_W/2;
        }else{
          peixe[p].posx -=(VELPEIXES);
        }
      }
    }
    vidinha.posy =vidinha.posy+(VELVIDINHA+dificuldade);
      switch(etapa){
        case 0:
        //  yfundo +=0.4;
          yfundo +=0.5;
        break;

        case 2:
        //  yfundo -=10;
        //  vidinha.posy -=VELVIDINHA;
          yfundo -=0.5;
        break;

        default:

        break;
      }

  //atualiza pedras

  //faz o peixe ir e voltar no eixo x


  }
  //  desenhaCena();
  //  glutSwapBuffers();
  DetectaColisoes();
  EtapasdoGame();
  glutPostRedisplay();
  glutTimerFunc(25, atualiza, 0);
}
// Rotina principal
int mainGame()
{

    srand(time(NULL));
    //fundo.posy =
    // Acordando o GLUT

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(W, H);
    // Abre a janela

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
