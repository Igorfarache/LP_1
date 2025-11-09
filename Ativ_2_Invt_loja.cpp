#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
using namespace std;

class Produto {
private:
    string nome;
    double preco;
    int estoque;
    string categoria;

public:
    Produto(string n, double p, int e, string c)
        : nome(n), preco(p), estoque(e), categoria(c) {}

    string getNome() const { return nome; }
    double getPreco() const { return preco; }
    int getEstoque() const { return estoque; }
    string getCategoria() const { return categoria; }

    void setPreco(double p) {
        if (p > 0) preco = p;
        else cout << "Erro: preço inválido.\n";
    }

    void addEstoque(int q) {
        if (q > 0) estoque += q;
        else cout << "Erro: quantidade inválida.\n";
    }

    void removeEstoque(int q) {
        if (q <= 0) {
            cout << "Erro: quantidade inválida.\n";
        } else if (q > estoque) {
            cout << "Erro: estoque insuficiente.\n";
        } else {
            estoque -= q;
        }
    }

    void exibir() const {
        cout << "Produto: " << nome << " | Categoria: " << categoria
             << " | Preço: R$ " << preco
             << " | Estoque: " << estoque << endl;
    }
};

class Inventario {
private:
    vector<Produto> produtos;                   
    set<string> categorias;                     
    map<string, int> contagemPorCategoria;      
    map<string, double> valorPorCategoria;      
    list<string> historicoVendas;               

public:
    // Construtor de produtos
    void addProduto(const Produto& p) {
        produtos.push_back(p);
        categorias.insert(p.getCategoria());
        contagemPorCategoria[p.getCategoria()]++;
        valorPorCategoria[p.getCategoria()] += p.getPreco() * p.getEstoque();
        cout << "Produto \"" << p.getNome() << "\" adicionado com sucesso.\n";
    }

    // Função que busca o produto pelo nome
    Produto* buscaProduto(const string& nome) {
        auto it = find_if(produtos.begin(), produtos.end(),
                          [&](const Produto& p) { return p.getNome() == nome; });
        if (it != produtos.end()) return &(*it);
        else return nullptr;
    }

    // Função que lista os produtos por cada categoria
    void lsPorCategoria(const string& cat) const {
        cout << "\nProdutos da categoria: \"" << cat << "\":\n";
        for (const auto& p : produtos) {
            if (p.getCategoria() == cat) p.exibir();
        }
    }

    // Função que calcula o valor total do inventário
    double valorTotalInv() const {
        double total = 0;
        for (const auto& p : produtos)
            total += p.getPreco() * p.getEstoque();
        return total;
    }

    // Função que registra a venda
    void rgstVenda(const string& nome, int quantidade) {
        Produto* p = buscaProduto(nome);
        if (p) {
            if (quantidade > 0 && quantidade <= p->getEstoque()) {
                p->removeEstoque(quantidade);
                historicoVendas.push_back(nome + " (" + to_string(quantidade) + ")");
                valorPorCategoria[p->getCategoria()] -= p->getPreco() * quantidade;
                cout << "Venda registrada: " << quantidade << "x " << nome << endl;
            } else {
                cout << "Erro: quantidade inválida ou insuficiente.\n";
            }
        } else {
            cout << "Produto não encontrado.\n";
        }
    }

    // Função que mostra o histórico de vendas
    void exibeHistorico() const {
        cout << "\nHistórico de Vendas:\n";
        for (const auto& item : historicoVendas)
            cout << item << endl;
    }

    // Exibir categorias e informações agregadas
    void rsmCategorias() const {
        cout << "\nResumo por Categoria:\n";
        for (const auto& c : categorias) {
            cout << "Categoria: " << c
                 << "\nProdutos: " << contagemPorCategoria.at(c)
                 << "\nValor total: R$ " << valorPorCategoria.at(c) << endl;
        }
    }
};

int main() {
    Inventario loja;
    //adicionando produtos
    loja.addProduto(Produto("Camiseta", 49.90, 10, "Roupas"));
    loja.addProduto(Produto("Calça Jeans", 89.90, 5, "Roupas"));
    loja.addProduto(Produto("Tênis", 199.90, 3, "Calçados"));
    loja.addProduto(Produto("Boné", 39.90, 7, "Acessórios"));
    //listando produtos pela categoria de roupas
    loja.lsPorCategoria("Roupas");
    //calculando o valor totaL do inventário
    cout << "\nValor total do inventário: R$ " << loja.valorTotalInv() << endl; 
    //mostrando o registro de venda de camisetas e tênis
    loja.rgstVenda("Camiseta", 2);
    loja.rgstVenda("Tênis", 1);
    //exibindo histórico de vendas
    loja.exibeHistorico();
    // Exibe as categorias, quantidade de produtos por categoria e valores
    loja.rsmCategorias();

    return 0;
}
