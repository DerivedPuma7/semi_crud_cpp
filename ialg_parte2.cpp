/*Identificação da dupla:

alunos = {
	1:{
		Nome: Gustavo Ribeiro de Figueiredo
		Número de matrícula: 201910617
		Turma: 22C
	},
	2:{
		Nome: Gustavo Henrique Miele Fraga
		Número de matrícula: 201820373
		Turma: 22C
	}
}

Tema do trabalho: Frutas tropicais
*/
#include <iostream>
using namespace std;

struct frutas{
	int id;
	string nome;
	string regiao;
	float calorias;
	string cor;
};

struct identificador{
	int id = 1;
	
	void incrementar(){
		id++;
	}
};

int mostrarMenu(){
	string opcao;
	cout << "Escolha uma opcao: " << endl;
	cout << "Cadastrar" << " | " << "Listar" << " | " << "Pesquisar" << " | " << "Alterar" << " | " << "Sair" << endl;
	
	cin >> opcao;
	
	if(opcao == "Cadastrar"){
		return 1;
	}
	else if(opcao == "Listar"){
		return 2;
	}
	else if(opcao == "Pesquisar"){
		return 3;
	}
	else if(opcao == "Alterar"){
		return 4;
	}
	else if(opcao == "Sair"){
		return -1;
	}
	
	return 0;
}

void cadastrarItem(frutas fruta[], identificador &fruta_id, int &quantidadeItens){
	string novoNomeFruta, novaRegiaoFruta, novaCorFruta;
	float novaCaloriaFruta;
	
	if(quantidadeItens >= 99){
		cout << "Não é possível inserir outro registro" << endl;
		return;
	}
	
	cout << endl;
	cout << "Insira o Nome, a Regiao, as Calorias e a Cor da fruta. Cada item deve ser inserido em uma linha diferente" << endl;
	cout << endl;
	
	cin.ignore();
	getline(cin, novoNomeFruta);
	getline(cin, novaRegiaoFruta);
	cin >> novaCaloriaFruta;
	cin.ignore();
	getline(cin, novaCorFruta);
	
	fruta[quantidadeItens].id = fruta_id.id;
	fruta[quantidadeItens].nome = novoNomeFruta;
	fruta[quantidadeItens].regiao = novaRegiaoFruta;
	fruta[quantidadeItens].calorias = novaCaloriaFruta;
	fruta[quantidadeItens].cor = novaCorFruta;
	
	cout << endl;
	cout << "Fruta inserida com sucesso" << endl;
	cout << endl;
	
	fruta_id.incrementar();
	quantidadeItens++;
	
	//INICIO ORDENAÇÃO 
	int tam = quantidadeItens;
	string vetorNome[tam], vetorCor[tam], vetorRegiao[tam];
	int vetorId[tam];
	float vetorCaloria[tam];
	
	for(int i = 0; i < quantidadeItens; i++){
		vetorId[i] = fruta[i].id;
		vetorNome[i] = fruta[i].nome;
		vetorRegiao[i] = fruta[i].regiao;
		vetorCaloria[i] = fruta[i].calorias;
		vetorCor[i] = fruta[i].cor;
	}
	
	int j;
	string valor_pivo, valor_regiao, valor_cor;
	float valor_calorias;
	int valor_id;
	
	for(int i = 1; i < tam; i++){
		valor_id = vetorId[i];
		valor_pivo = vetorNome[i];
		valor_regiao = vetorRegiao[i];
		valor_calorias = vetorCaloria[i];
		valor_cor = vetorCor[i];
		
		j = i - 1;
		while((j >= 0) and (valor_pivo < vetorNome[j])){
			vetorNome[j + 1] = vetorNome[j];

			fruta[j + 1].id = vetorId[j];
			fruta[j + 1].nome = vetorNome[j];
			fruta[j + 1].regiao = vetorRegiao[j];
			fruta[j + 1].calorias = vetorCaloria[j];
			fruta[j + 1].cor = vetorCor[j];
			j--;
		}
		vetorNome[j + 1] = valor_pivo;

		fruta[j + 1].id = valor_id;
		fruta[j + 1].nome = valor_pivo;
		fruta[j + 1].regiao = valor_regiao;
		fruta[j + 1].calorias = valor_calorias;
		fruta[j + 1].cor = valor_cor;
	}
	// FIM ORDENAÇÃO
}

void listarItens(frutas fruta[], int quantidadeItens){
	cout << endl;
	cout << "Veja a seguir a relacao dos itens cadastrados no sistema:" << endl;
	cout << "| id_fruta |" << "  nome_fruta |" << " regiao_fruta |" << " caloria_fruta |" << "  cor_fruta  |" << endl;
	
	for(int i = 0; i < quantidadeItens; i++){
		cout << "|   " << fruta[i].id << "      |     " << fruta[i].nome << "      |     " << fruta[i].regiao << "      |     " << fruta[i].calorias << "      |     " << fruta[i].cor << endl;
	}
	
	cout << endl;
}

int buscarItem(frutas fruta[], int quantidadeItens, bool isEdit){
	string resposta;
	string respostaSecundaria;
	string nomeFruta;
	//variaveis busca binaria
	int pos_inicial = 0, pos_final = quantidadeItens;
	int posicao = -1;
	int meio;
	//variaveis busca sequencial
	string corResposta, regiaoResposta;
	int idResposta, i = 0;
	float caloriasResposta;
	
	if(isEdit){
		cout << endl;
		cout << "Para alterar um registro, so e permitido alterar pelo seu id" << endl;
		cout << "Insira o id que deseja alterar" << endl;
		cin >> idResposta;
			
		while((i < quantidadeItens) && (fruta[i].id != idResposta)){
			i++;
		}
	
		if(i != quantidadeItens){
			posicao = i; 
		}
		
		return posicao;
	}
	
	cout << endl;
	cout << "Voce deseja buscar pelo nome da fruta ? S/N" << endl;
	cin >> resposta;
	
	//busca binaria pelo nome da fruta
	if(resposta == "S"){
		cout << endl;
		cout << "Insira o nome da fruta que deseja buscar" << endl;
		cin.ignore();
		getline(cin, nomeFruta);
		
		//inicio busca binaria
		while(pos_inicial <= pos_final){
			meio = (pos_inicial + pos_final) / 2;
		
			if(nomeFruta == fruta[meio].nome){
				posicao = meio;
				pos_inicial = pos_final + 1; //parar o while
			}
			else{
				if(nomeFruta > fruta[meio].nome){
					pos_inicial = meio + 1;
				}
				else{
					pos_final = meio - 1;
				}
			}
			//fim busca binaria
		}
	}
	else{
		cout << endl;
		cout << "Dentre os campos a seguir, por qual deles quer fazer a busca ?" << endl;
		cout << "id, regiao, calorias, cor" << endl;
		cin >> respostaSecundaria;
		
		//busca sequencial pelo id
		if(respostaSecundaria == "id"){
			cout << endl;
			cout << "Insira o id que deseja buscar" << endl;
			cin >> idResposta;
			
			while((i < quantidadeItens) && (fruta[i].id != idResposta)){
				i++;
			}
	
			//saimos do while quando encontramos o elemento 'K'. Assim, 'posicao' assume 'i'
			if(i != quantidadeItens){
				posicao = i; 
			}
			
		}
		//busca sequencial pela regiao
		if(respostaSecundaria == "regiao"){
			cout << endl;
			cout << "Insira a regiao que deseja buscar" << endl;
			cin >> regiaoResposta;
			
			while((i < quantidadeItens) && (fruta[i].regiao != regiaoResposta)){
				i++;
			}
	
			//saimos do while quando encontramos o elemento 'K'. Assim, 'posicao' assume 'i'
			if(i != quantidadeItens){
				posicao = i; 
			}
			
		}
		//busca sequencial pela cor
		if(respostaSecundaria == "cor"){
			cout << endl;
			cout << "Insira a cor que deseja buscar" << endl;
			cin >> corResposta;
			
			while((i < quantidadeItens) && (fruta[i].cor != corResposta)){
				i++;
			}
	
			//saimos do while quando encontramos o elemento 'K'. Assim, 'posicao' assume 'i'
			if(i != quantidadeItens){
				posicao = i; 
			}
			
		}
		//busca sequencial pela caloria
		if(respostaSecundaria == "calorias"){
			cout << endl;
			cout << "Insira a caloria que deseja buscar" << endl;
			cin >> caloriasResposta;
			
			while((i < quantidadeItens) && (fruta[i].calorias != caloriasResposta)){
				i++;
			}
	
			//saimos do while quando encontramos o elemento 'K'. Assim, 'posicao' assume 'i'
			if(i != quantidadeItens){
				posicao = i; 
			}
			
		}
		
	}
	
	if(posicao == -1){
		return -1;
	}
	return posicao;
}

void editarItem(frutas fruta[], int quantidadeItens){
	int posicaoFruta;
	
	string novoNomeFruta, novaRegiaoFruta, novaCorFruta;
	float novaCaloriaFruta;
	
	posicaoFruta = buscarItem(fruta, quantidadeItens, true);
	
	cout << endl;
	
	if(posicaoFruta == -1){
		cout << "Fruta nao encontrada" << endl;
		cout << endl;
		return;
	}
	
	cout << "A seguir, voce estara alterando esse registro:" << endl;
	cout << "| id_fruta |" << "  nome_fruta |" << " regiao_fruta |" << " caloria_fruta |" << "  cor_fruta  |" << endl;
	cout << "|   " << fruta[posicaoFruta].id << "      |     " << fruta[posicaoFruta].nome << "      |     " << fruta[posicaoFruta].regiao << "      |     " << fruta[posicaoFruta].calorias << "      |     " << fruta[posicaoFruta].cor << endl;
	
	cout << endl;
	cout << "Insira o Nome, a Regiao, as Calorias e a Cor da fruta. Cada item deve ser inserido em uma linha diferente" << endl;
	cout << endl;
	
	
	cin.ignore();
	getline(cin, novoNomeFruta);
	getline(cin, novaRegiaoFruta);
	cin >> novaCaloriaFruta;
	cin.ignore();
	getline(cin, novaCorFruta);
	
	
	fruta[posicaoFruta].nome = novoNomeFruta;
	fruta[posicaoFruta].regiao = novaRegiaoFruta;
	fruta[posicaoFruta].calorias = novaCaloriaFruta;
	fruta[posicaoFruta].cor = novaCorFruta;
	
	cout << endl;
	cout << "Registro alterado com sucesso" << endl;
	cout << endl;
	
	
}

int main(){	
	const int limite = 100;
	int acao;
	int quantidadeItens = 0;
	
	frutas fruta[limite];
	identificador fruta_id;
	
	do{
		acao = mostrarMenu();
		
		switch(acao){
			case(0):
				break;
			case(1):
				cadastrarItem(fruta, fruta_id, quantidadeItens);
				break;
			case(2):
				listarItens(fruta, quantidadeItens);
				break;
			case(3):
				int posicao;
				posicao = buscarItem(fruta, quantidadeItens, false);
				if(posicao == -1){
					cout << "Essa fruta nao foi encontrada" << endl;
					cout << endl;
				}
				else{
					cout << endl;
					cout << "Fruta encontrada" << endl;
					cout << "| id_fruta |" << "  nome_fruta |" << " regiao_fruta |" << " caloria_fruta |" << "  cor_fruta  |" << endl;
					cout << "|   " << fruta[posicao].id << "      |     " << fruta[posicao].nome << "      |     " << fruta[posicao].regiao << "      |     " << fruta[posicao].calorias << "      |     " << fruta[posicao].cor << endl;
					cout << endl;
				}
				break;
			case(4):
				editarItem(fruta, quantidadeItens);
				break;
			case(-1):
				return 0;
				break;
			default:
				break;
		}
	}while(true);
	
}
