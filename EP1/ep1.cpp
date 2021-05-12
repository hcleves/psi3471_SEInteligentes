#include <cekeikon.h>
#include <math.h>
#include <fstream>
#include <cstdlib>

void achamaior(Mat_<FLT> resultado,float& maior,int& coordx,int& coordy);
void desenhacirculo(Mat_<COR> imagem,float raio, float padding, int centrox, int centroy);
double porcentagemvermelho(Mat_<COR> imagem,int minLinha,int maxLinha,int minColuna,int maxColuna);

int main(int argc, char** argv){
    if(argc<4){
        cout << "Numero de argumentos insuficientes\n";
        cout << "Para utilizar o programa o comando deve ser assim: ep1 nome_de_entrada.extensao nome_de_saida 7\n";
        return 0;
    }
    srand(100);
    int template_size;

    if(argc==4){
        template_size=strtol(argv[3], NULL, 10);
    }else{
        template_size=7;
    }

    String tipo[7]={"E","D","E","E","D","D","D"};
    Mat_<FLT> resultado;
    Mat_<COR> original,templ,acolor;
    Mat_<COR> colorida;
    float results[8][26]={0};
    int coordresults[8][26][2]={0};
    int tamanhoinicial = 50;
    String template_name;
    int contador=0;
    int contador2=0;
    int tamanho=0;
    int limcont2=26;

    le(acolor, argv[1]);
    //este loop varia o arquivo do template
    for(contador=0; contador<template_size; contador++){
        template_name="am"+ to_string(contador) + ".jpg";
        le(original,template_name);

        //este loop varia o tamanho do template
        for(contador2=0;contador2<limcont2;contador2++){
            tamanho=tamanhoinicial+10*contador2;
            resize(original,templ,Size(tamanho,tamanho),0,0,INTER_AREA);
            matchTemplate(acolor,templ,resultado,CV_TM_CCOEFF_NORMED);
            float maior=-FLT_MAX;
            int coordx,coordy;
            achamaior(resultado,maior,coordx,coordy);
            results[contador][contador2]=maior;
            coordresults[contador][contador2][0]=coordx;
            coordresults[contador][contador2][1]=coordy;
        }
    }

    int locx,locy;
    float maior;

    le(colorida,argv[1]);
    maior=-FLT_MAX;
    //procura o maior resultado em meio a matriz com os maiores valores dos template matching
    for(contador=0;contador<template_size;contador++){
        for(contador2=0;contador2<limcont2;contador2++){
            if(maior<results[contador][contador2]){
                //os resultados só são validos se forem diferentes de 1 e se tiver pelo menos 20% de pixeis "vermelhos" na area escolhida
                if(results[contador][contador2]!=1 && porcentagemvermelho(colorida,coordresults[contador][contador2][0],coordresults[contador][contador2][0] + tamanhoinicial+10*contador2,coordresults[contador][contador2][1],coordresults[contador][contador2][1]+tamanhoinicial+10*contador2)>0.2){
                    maior=results[contador][contador2];
                    locx=contador;
                    locy=contador2;
                }
            }
        }
    }
    String palavra=argv[2];

    tamanho=tamanhoinicial+10*locy;
    //desenha o circulo onde está a placa
    desenhacirculo(colorida,tamanho/2,tamanho/40,coordresults[locx][locy][0]+tamanho/2,coordresults[locx][locy][1]+tamanho/2);
    //desenha um "ponto" no centro da placa
    desenhacirculo(colorida,5,5,coordresults[locx][locy][0]+tamanho/2,coordresults[locx][locy][1]+tamanho/2);

    imp(colorida , palavra + "_"+ tipo[locx] + ".jpg");
    return 0;
}

void achamaior(Mat_<FLT> resultado,float& maior,int& coordx,int& coordy){
    for (int i=0;i<resultado.rows;i++){
        for (int j=0;j<resultado.cols;j++){
            if(resultado(i,j)>maior){
                maior=resultado(i,j);
                coordx=i;
                coordy=j;
            }
        }
    }
    return;
}

void desenhacirculo(Mat_<COR> imagem,float raio, float padding, int centrox, int centroy){
    double distance;
    for (int i=0;i<imagem.rows;i++){
        for (int j=0;j<imagem.cols;j++){
            distance = sqrt(pow(i-centrox,2)+pow(j-centroy,2));
            if(distance>raio-padding && distance<raio+padding){
                imagem(i,j)[1]=255;
            }
        }
    }
    
    return;
}

double porcentagemvermelho(Mat_<COR> imagem,int minLinha,int maxLinha,int minColuna,int maxColuna){
    int soma=0,total;
    Mat_<GRY> redColorOnly;
    inRange(imagem, Scalar(0,2,71), Scalar(85, 79, 255), redColorOnly);
    for(int i=minLinha;i<maxLinha;i++){
        for(int j=minColuna;j<maxColuna;j++){
            if(redColorOnly[i][j]==255){
                soma++;
            }
        }
    }
    total = (maxLinha-minLinha)*(maxColuna-minColuna);
    return (double) (double)soma/(double)total;
}