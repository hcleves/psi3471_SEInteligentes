//funcao aumentaTreino alterada. Essa funcao esta originalmente no arquivo "cektiny.h"
void aumentaTreino(vector<vec_t>& timg, vector<label_t>& tlab, int nl, int nc, 
int ns, 
 bool bespelha=false, bool diagonais=false) {
 if (timg.size()!=tlab.size()) xerro1("Erro: Dimensoes diferentes timg e tlab");
 if (ns!=1 && ns!=3) xerro1("Erro aumentaTreino: deve ter ns==1 ou ns==3");
 int escala = 1;
 if (bespelha) {
 unsigned tamanho=timg.size();
 for (unsigned i=0; i<tamanho; i++) {
 if(i%escala==0){
 timg.push_back( espelha( timg[i],nl,nc,ns ) ); tlab.push_back( tlab[i] );
 }
 }
 }
 unsigned tamanho=timg.size();
 for (unsigned i=0; i<tamanho/2; i++) {
 if(i%escala==0){
 timg.push_back( deslocaEsquerda( timg[i],nl,nc,ns ) ); tlab.push_back( 
tlab[i] );
 timg.push_back( deslocaDireita( timg[i],nl,nc,ns ) ); tlab.push_back( 
tlab[i] );
 timg.push_back( deslocaCima( timg[i],nl,nc,ns ) ); tlab.push_back( 
tlab[i] );
 timg.push_back( deslocaBaixo( timg[i],nl,nc,ns ) ); tlab.push_back( 
tlab[i] );
 }
 }
 if (diagonais) {
 unsigned tamanho=timg.size();
 for (unsigned i=0; i<tamanho; i++) {
 if(i%escala==0){
 timg.push_back( deslocaCima( deslocaEsquerda( timg[i],nl,nc,ns ), 
nl,nc,ns) ); 
 tlab.push_back( tlab[i] );
 timg.push_back( deslocaCima( deslocaDireita( timg[i],nl,nc,ns ), 
nl,nc,ns) ); 
 tlab.push_back( tlab[i] );
 timg.push_back( deslocaBaixo( deslocaEsquerda( timg[i],nl,nc,ns ), 
nl,nc,ns) ); 
 tlab.push_back( tlab[i] ); timg.push_back( deslocaBaixo( deslocaDireita( timg[i],nl,nc,ns ), 
nl,nc,ns) ); 
 tlab.push_back( tlab[i] );
 }
 }
 }
