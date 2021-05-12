## Nota

Todos os modelos foram rodados no meu computador pessoal sem nenhum outro programa competindo por uso de cpu. 


## Modelos Testados

Primeira rede testada. Com 10 epochs, obteve 98% na validação e 80% no teste. Demorou 140s 
para treinamento. Apresentou grande quantidade de overfitting, pois o resultado na validação foi muito 
superior ao do teste.

```
net << conv(300, 250, 5, 1, 40)
 << max_pool(296, 246, 40, 4) << relu()
 << conv(74, 61, 5, 40, 80)
 << max_pool(70, 57, 80, 2) << relu()
 << fc(35*28*80, 200) << relu()
 << fc(200,20) << relu
 ```
 
 Segunda rede testada. Aumentei a janela no segundo max_pool. Com 10 epochs, obteve 88% na 
validação e 81% teste. Demorou 94.1s para treinamento. Apresentou menos overfitting, mas a taxa de 
acerto ainda é baixa. 

```
net << conv(300, 250, 5, 1, 40)
 << max_pool(296, 246, 40, 4) << relu()
 << conv(74, 61, 5, 40, 80)
 << max_pool(70, 57, 80, 4) << relu()
 << fc(17*14*80, 200) << relu()
 << fc(200,20) << relu()
 << fc(20, 2);
```

Terceira rede testada. Aumentei o número de neurônios na camada fully-connected. Com 10 
epochs, obteve 92% na validação e 79% no teste. Demorou 109s para treinamento. Teve maior Overffiting 
que a primeira rede e uma taxa de acerto ainda mais baixa. Portanto, descartei a ideia de aumentar a 
quantidade de neurônios.

```
net << conv(300, 250, 5, 1, 40)
 << max_pool(296, 246, 40, 4) << relu()
 << conv(74, 61, 5, 40, 80)
 << max_pool(70, 57, 80, 4) << relu()
 << fc(17*14*80, 400) << relu()
 << fc(400,40) << relu()
 << fc(40, 2); 
```

Quarta rede testada. Adicionei uma terceira camada de convolução. Com 10 epochs, obteve 91% 
na validação e 78% no teste. Demorou 125s. Também apresentou alto overfitting

```
net << conv(300, 250, 5, 1, 40)
 << max_pool(296, 246, 40, 4) << relu()
 << conv(74, 61, 5, 40, 80)
 << max_pool(70, 57, 80, 4) << relu()
 << conv(17, 14, 3, 80, 160) 
 << max_pool(15,12,160,2) << relu() 
 << fc(7*6*160, 200) << relu()
 << fc(200,20) << relu()
 << fc(20, 2);
```

Quinta rede testada. Mesma arquitetura da segunda, porem com primeiro max_pool com janela 
de 8. Com 10 epochs, obteve 90% de validação e 90% de teste. Demorou 44s. Apresentou nenhum 
overfitting, com uma taxa de acerto alta e também muito rápida. Melhor rede até o momento. Essa 
arquitetura de rede parecia promissora. Portanto, testei várias redes com a mesma arquitetura variando 
o tamanho da janelas dos max_pooling e das convolucoes. Os resultados foram piores que o da Quinta 
rede, e para não alongar demais esse relatório, não irei inclui-las. Aumentar o número de epochs também 
apenas piorava o desempenho da rede. 

```
net << conv(300, 250, 5, 1, 40)
 << max_pool(296, 246, 40, 8) << relu()
 << conv(37, 30, 5, 40, 80)
 << max_pool(33, 26, 80, 4) << relu()
 << fc(8*6*80, 200) << relu()
 << fc(200,20) << relu()
 << fc(20, 2);
```

Sexta rede testada. Arquitetura inspirada na AlexNet[6]. A primeira convolução é feita com stride 
4. Também é utilizado camadas de dropout. E a última camada é avaliada com uma função de softmax. 
Com 30 epochs, obteve 91% na validação e 81% no teste. Demorou 967s para treinamento. Como essa 
rede apresentava mais variáveis, foi necessário 30 epochs para ela começar a funcionar bem. Porém, 
ainda não apresentou um resultado satisfatório

```
net << conv(300, 250, 7, 1, 96, padding::valid, true, 4, 4)
 << relu() << max_pool(74, 61, 96, 2) 
 << conv(37, 30, 5, 96, 256, padding::valid, true, 1, 1)
 << relu() << max_pool(33, 26, 256, 2) 
 << conv(16, 13, 3, 256, 256, padding::valid, true, 1, 1)
 << relu() << max_pool(14, 11, 256, 2) 
 << fc(7*5*256, 512) << relu() << dropout(512,0.5)
 << fc(512,512) << relu() << dropout(512,0.5)
 << fc(512, 2) << softmax();
```

Sétima rede testada. Utilizando o dropout para reduzir overfitting, resolvi acrescenta-la na 
primeira rede. Com 10 epochs, obteve 90% na validação e 85% teste. Demorou 147s. Como esperado, 
diminui bastante o overfitting, porém, ainda obteve performance pior que a Quinta rede. Testei também 
o acréscimo de dropout nas outras redes com overfitting. O overfitting diminuiu em todas, porem a 
performance não subiu o suficiente. 

```
net << conv(300, 250, 5, 1, 40)
 << max_pool(296, 246, 40, 4) << relu()
 << conv(74, 61, 5, 40, 80)
 << max_pool(70, 57, 80, 2) << relu()
 << fc(35*28*80, 200) << relu() << dropout(200,0.3)
 << fc(200,20) << relu()
 << fc(20, 2);
 ```
 
 Para facilitar o design das redes a partir de agora, decidi incluir no csv.h a chamada da função 
resize para transformar as imagens de 300x250 para 256x256.
Oitava rede testada. Seguindo a arquitetura inspirada pela AlexNet, porem o pooling é feito com 
janelas de tamanho 3 e stride tamanho 2. Também removi as camadas de dropout e softmax. Com 50 
epochs obteve 50% de validação e 50% de teste. Demorou 1376s de treinamento. Como nem começou a 
funcionar após 1376s de treinamento, descartei essa rede. 

```
net << conv(256, 256, 11, 1, 96, padding::valid, true, 4, 4)
 << max_pool(62, 62, 96, 3, 2) << relu()
 << conv(30, 30, 5, 96, 256, padding::valid, true, 1, 1 )
 << max_pool(26, 26, 256, 3, 2) << relu()
 << conv(12, 12, 3, 256, 256, padding::valid, true, 1, 1)
 << max_pool(10, 10, 256, 3, 2) << relu()
 << fc(4*4*256,256) << relu()
 << fc(256,20) << relu()
 << fc(20,2); 
 ```
 
 Nona rede testada. Mesma rede da Quinta, porem agora com imagens 256x256. Com 30 epochs 
obteve 89% de validação e 88% teste. Demorou 122s para treinamento. Não houve melhorias 
significativas.

```
net << conv(256, 256, 5, 1, 40) 
 << max_pool(252, 252, 40, 8) << relu()
 << conv(31.0, 31.0, 5, 40, 80) 
 << max_pool(27.0, 27.0, 80, 4) << relu()
 << fc(6*6*80, 200) << relu()
 << fc(200,20) << relu()
 << fc(20,2);
 ```
 
 Decima rede testada. Essa rede é um pouco mais profunda, com 5 camadas de convolução, sendo
a última sem pooling. Com 50 epochs obteve 50% de validação e 50% de teste. Demorou 859s. Como 
demorou demais e não apresentou resultado, fiz alterações.

```
net << conv(256, 256, 5, 1 , 16) 
 << max_pool(252, 252, 16, 2) 
 << conv(126, 126, 5, 16, 32) 
 << max_pool(122, 122 , 32, 2) 
 << conv(61, 61, 5, 32, 64)
 << max_pool(57, 57, 64, 2)
 << conv(28, 28, 5, 64, 128) 
 << max_pool(24, 24, 128, 2)
 << conv(12, 12, 3, 128, 256)
 << fc(10*10*256, 200) << relu()
 << fc(200,20) << relu()
 << fc(20,2);
 ```
 
 Decima primeira rede testada. Como a decima rede, porem começa com uma camada de 
max_pooling para reduzir a resolução pela metade e possui apenas 4 camadas de convolução. Com 50 
epochs obteve 93% na validação e 92% no teste. Demorou 243s. Essa rede apresentou o melhor 
desempenho até agora, com baixo overfitting e rápido treinamento. Aumentando o número de epochs, 
infelizmente, mantem o desempenho constante

```
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
 ```
 
Essa rede aparenta ter atingido um bom desempenho, com mais dados para treinamento a 
performance deve aumentar. Por conta disso, adicionei a função aumentaTreino. Porém, fiz uma 
alteração em um dos loops de aumentaTreino afim de diminuir o tempo de treinamento. A função 
aumentaTreino alterada pode ser encontrada no Anexo 1. A rede então, mostrou-se eficaz, atingindo um 
acerto de 98% na validação e 99% no teste. O tempo de treinamento aumentou bastante, entretanto. Foi 
necessário 3673s para completar os 50 epochs. Com 32 epochs, o tempo de treinamento foi de 2457s e o 
acerto de 98% em ambos validação e teste.
