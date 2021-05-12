//csv.h - rotina para ler arquivo CSV com nomes de imagens e rotulos
//Sera usada pelos programas treina.cpp e testa.cpp
#include <cektiny.h>
#include <cekeikon.h>
//<<<<<<<<<<<<<<<<< IMAGEM_CSV <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class ARQCSV {
//Le arquivo CSV com formato:
//111a.jpg;0
//111b.jpg;0
//Le imagem e label no mesmo diretorio do arquivo CSV e os coloca nos vetores x e y
public:
 int n; // numero de linhas do CSV
 vector<vec_t> x; vector<label_t> y; // imagens e rotulos convertidos para formato tiny_dnn
 vector< string > nome; // nomes dos arquivos
 ARQCSV(string caminho);
};
ARQCSV::ARQCSV(string arqcsv) {
 n=0;
 string nomedir=diretorio(arqcsv);
 //cout<< nomedir<< endl;
 if (nomedir=="") nomedir=".";
 FILE* arq=fopen(arqcsv.c_str(),"rt");
 while (true) {
 string st=leFileName(arq);
 if (st=="eof") break;
 int rot; leNum(arq,rot);
 n++;
 }
 x.resize(n);
 y.resize(n);
 nome.resize(n);
 rewind(arq);
 int i=0;
 Mat_<FLT> f;
 while (true) {
 string st=leFileName(arq);
 if (st=="eof") break;
 st=nomedir+'/'+st;
 int rot; leNum(arq,rot);
 le(f,st);
 //mostra(f);
 resize(f,f,Size(256,256),0,0,INTER_AREA);
 normalize(f,f,1,0,NORM_MINMAX);
 //mostra(f);
 converte(f,x[i]);
 y[i]=rot;
 nome[i]=st;
 i++;
 }
 fclose(arq);
}
