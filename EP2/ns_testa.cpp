#include "csv.h"
int main(int argc, char** argv) {
    network<sequential> net;
    net.load("ns_rede.net");
    string nomedir ="";
    if(argc>2){
        cout << "Quantidade de parametros invalidos. Passe apenas o diretorio" << endl;
        return 0;
    }else{
        if(argc==2) nomedir = std::string(argv[1]) + "/";
    }

    ARQCSV v(nomedir + "ns_valida.csv");
    ARQCSV q(nomedir + "ns_teste.csv");
    
    cout << "Taxa de erro de validacao: "  << 100 - net.test(v.x,v.y).accuracy() << "%" << endl;
    cout << "Arquivos de validacao classificados incorretamente: " << endl;
    for (unsigned i=0; i<v.x.size(); i++)
        if (net.predict_label(v.x[i])!=v.y[i])
            cout << v.nome[i] << endl;
    
    cout << "Taxa de erro de teste: " << 100 - net.test(q.x, q.y).accuracy() << "%" << endl;
    cout << "Arquivos de teste classificados incorretamente: "  << endl;
    for (unsigned i=0; i<q.x.size(); i++)
        if (net.predict_label(q.x[i])!=q.y[i])
            cout << q.nome[i] << endl;
}
