#include "csv.h"
int main(int argc, char** argv) {
    int n_train_epochs=50;
    int n_minibatch=10;
    int i;
    int posicao=0;
    bool verbose=false;
    string nome_dir="";
    for(i=0;i<argc;i++){
        if(strcmp(argv[i],"-v")==0){
            verbose=true;
            posicao=i;
        }
    }
    
    if(argc>3){
        cout << "numero de argumentos invalido" << endl;
        return 0;
    }
    if(posicao==0 && argc==2){
        nome_dir=std::string(argv[1]) + "/";
    }else if(posicao ==1 && argc==3){
        nome_dir=std::string(argv[2]) + "/";
    }else if(posicao==2 && argc==3){
        nome_dir=std::string(argv[1]) + "/";
    }else{
        cout << "argumentos invalidos" << endl;
        return 0;
    }

    ARQCSV a(nome_dir + "mf_treino.csv");
    ARQCSV v(nome_dir + "mf_valida.csv");
    
    network<sequential> net; 
 	net << max_pool(256, 256, 1, 2) 	
     << conv(128, 128, 5, 1, 16) 
	<< max_pool(124, 124 , 16, 2) 
	<< conv(62, 62.0, 5, 16, 32)
    << max_pool(58, 58, 32, 2)
    << conv(29, 29, 5, 32, 64) 
	<< max_pool(25, 25, 64, 2)
    << conv(12, 12, 3, 64, 128)
	<< fc(10*10*128, 200) << relu()
	<< fc(200,20) << relu()
	<< fc(20,2);

    if(a.x.size()==0){
        cout << "Falha ao abrir as imagens. O diretorio pode estar incorreto." << endl;
        return 0;
    }
    aumentaTreino(a.x,a.y,256,256,1,false,true); //espelha, diagonais
    adam optimizer;
    optimizer.alpha = 5e-5;
    if(verbose) cout << "Learning rate=" << optimizer.alpha << endl;
    int sucesso_anterior=0;
    if(verbose) cout << "start training" << endl;
    
    timer t;
    double total_tempo = 0;
    int epoch = 1;
    int total = 0;
    int omelhor=-1;
    auto on_enumerate_epoch = [&]() {
        if(verbose)  cout << "Epoch " << epoch << "/" << n_train_epochs << " finished. " << t.elapsed() << "s elapsed. ";
        total_tempo = total_tempo + t.elapsed();
        ++epoch;
        result res = net.test(v.x, v.y);
        if(verbose)  cout << "Validacao: " << res.num_success << "/" << res.num_total << endl;
        if (res.num_success<=sucesso_anterior && optimizer.alpha>5e-6) {
            optimizer.alpha *= 0.80;
            if(verbose)  cout << "Learning rate=" << optimizer.alpha << endl;
        }
        sucesso_anterior=res.num_success;

        if (omelhor<=res.num_success) {
            omelhor=res.num_success;
            total=res.num_total;
            string nomearq = "mf_rede.net";
            net.save(nomearq);
            if(verbose)  cout << "Gravado arquivo " << nomearq << endl;
        }
        t.restart();
    };

    auto on_enumerate_minibatch = [&]() { };
    net.train<mse>(optimizer, a.x, a.y, n_minibatch,
    n_train_epochs, on_enumerate_minibatch, on_enumerate_epoch);
    net.save("mf_rede.net");
    cout << "A menor taxa de erro de validacao: " << (1-((double)omelhor)/(double(total)))*100 << "%" << endl; 
    cout << "Tempo de processamento:" << total_tempo << "s " << endl;
}