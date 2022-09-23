# Penguin Cafe

Um café onde penguins servem comida para outros penguins

Ninguém nunca teve essa ideia antes, confia. Favor não olhar o click jogos.
https://www.crazygames.com/game/penguin-diner

# 3 leis de Gastal

- No MÁXIMO 15% de código pronto (exceto desenvolvido em aulas práticas)
- Sempre que utilizar código pronto, comentar com "FONTE" para que possa ser identificado com facilidade
- Proibido uso de funções 'glu' que simplificam a manipulação de vetores e tal
	- gluLookAt()
	- gluOrtho2D()
	- gluPerspective()
	- gluPickMatrix()
	- gluProject()
	- gluUnProject()
	- glm::lookAt()
	- glm::ortho()
	- glm::perspective()
	- glm::pickMatrix()
	- glm::rotate()
	- glm::scale()
	- glm::translate()
	- dentre outras

# Requisitos

Mais detalhes dos requisitos podem ser vistos no [Moodle da cadeira](https://moodle.inf.ufrgs.br/mod/assign/view.php?id=112199)

- [ ] Interação em Tempo Real
- [ ] Objetivo/Lógica não-trivial
- [X] Utiliza as matrizes vista em aula
- [X] Interação com usuário utilizando teclado e mouse
- [X] Malhas poligonais complexas
  - [X] Um modelo mais complexo que a vaca
- [X] Transformações geométricas em outros objetos além da câmera
- [X] Controle de câmeras virtuais
  - [X] Câmera Look-At
  - [X] Câmera Livre
- [X] Diversas instâncias do mesmo objeto, com diferentes matrizes de modelo
- [ ] Testes de intersecção entre objetos virtuais
  - [ ] Três tipos de teste de intersecção
    - Teste Cubo-Cubo
    - Teste Cubo-Plano
    - Teste Ponto-Esfera
  - [ ] Arquivo nomeado collisions.cpp
- [ ] Modelos de iluminação
  - [ ] Lambert **E** Blinn-Phong
  - Interpolação de Iluminação
    - [ ] Gouraud
    - [ ] Phong
- [X] Mapeamento de Texturas
  - [X] Dois objetos 
- [ ] Curva de Bézier
  - [ ] Um objeto cujo caminho é definido por curva de Bézier
- [X] Animação de Movimento baseada no tempo
  - [X] Todas as movimentações de objetos (incluindo da câmera) devem ser computadas baseado no tempo.

# Compilação

Para compilar o código com biblioteca estática, basta buildar o target `PenguinCafe`.   
Caso prefira utilizar bibliotecas dinâmicas, disponibilizamos o target `PenguinCafeDLL`.

Na pasta `lib` estão disponilizadas as bibliotecas. Utilizamos o GLFW do mingw64, porém, caso precise mudar para outro compilador ou plataforma
basta modificar os arquivos que estão na pasta e o resto da compilação deve funcionar corretamente.

# Tarefas

- [X] Organizar código atual em diferentes pacotes
	- [X] File Handling
	- [X] Rendering
	- [X] Player Movement
	- [X] Apenas código do GLFW na main
- [X] Mapear funcionalidades
- [X] Descobrir como enviar dados de objetos uma vez só para a GPU (Vamos suportar apenas UV mapping)
- [X] Descobrir como ter várias texturas em um shader só
  - [X] Utilizar um ID para selecionar qual textura está sendo utilizada
  - [X] Utilizar textura definida no material (No Need)
- [ ] Implementar primeira pessoa
  - [ ] Talvez precise de um shader específico 
- [ ] Suportar especularidade
  - [ ] Implementar modelos de iluminação 
- [ ] Definir escopo do jogo
- [ ] Implementar lógica de jogo
- [ ] Implementar colisão
- [ ] Criar cena que será utilizada no jogo
- [ ] Definir quais objetos vamos utilizar
  - [ ] "Limpar" objetos 
  - [ ] Linkar referências dos objetos/texturas
  - [X] Não esquecer de um modelo altamente complexo

# Referências

Por enquanto, somente coisas utilizadas durante a cadeira.

## Código

- Coisas dos labs
- Tudo original 😎
- Polimorfismo 🪿

## Modelos/Texturas
