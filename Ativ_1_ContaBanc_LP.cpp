#include <iostream>
#include <string>
using namespace std;

class Cliente {
// Atributos privados da classe Cliente
private:
    string nome;
    string cpf;
    
public:   
    //Construtor CLiente com parâmetro e sem, inicializa os atributos
    Cliente() {
    nome = "";
    cpf = "";
    }
    
    Cliente (string n, string c){
        nome = n;
        cpf = c;
    }
    // getter para nome
    string getNome(){
        return nome;
    }
    // getter para cpf
    string getCpf(){
        return cpf;
    }

};

class ContaBancaria {
// Atributos privados da classe ContaBancaria
private: 
    int numero;
    double saldo;
    Cliente titular;
    
public:
    // Construtor ContaBancaria, inicializa os atributos
    ContaBancaria (int num, Cliente t, double s = 0.0){
        numero = num;
        saldo = s;
        titular = t;
    }
    // método depositar, verifica se o valor é ou não positivo para validar o depósito
    void depositar(double valor){
        if (valor > 0){
            saldo += valor;
            cout << "Deposito de R$ " << valor << " Realizado na conta " << numero << endl;
        } else {
            cout << "Valor de deposito inválido!" << endl;
        }
    }
    // método sacar, verifica se é possivel ou não sacar dinheiro e se o saldo é suficiente
    void sacar(double valor){
        if (valor <= 0){
            cout << "Valor de saque inválido!" << endl;
        } else if (valor > saldo){
            cout << "Saldo insuficiente para saque!" << endl;
        } else {
            saldo -= valor;
            cout << "Saque de R$ " << valor << " realizado na conta " << numero << endl;
        }
    }
    // método transferir, Transfere valor de apenas uma conta para outra
    void transferir(double valor, ContaBancaria &destino){
        if (valor <= 0){
            cout << "Valor de transferência inválido!" << endl;
        } else if (valor > saldo){
            cout << "Saldo insuficiente para transferência!" << endl;
        } else {
            saldo -= valor;
            destino.depositar(valor); // chama depositar para respeitar o encapsulamento, facilitar manutenções futuras e reaproveitar código
            cout << "Transferido: R$ " << valor << " da conta " << numero << " para a conta " << destino.numero << endl;
        }
    }
    // método transferir (2), transfere valor de uma conta para mais de uma conta, dividindo igualmente
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2){
        double metade = valor / 2.0;
        if (valor <= 0){
            cout << "Valor de transferência inválido!" << endl;
        } else if (valor > saldo) {
            cout << "Saldo insuficiente para transferência!" << endl;
        } else {
            saldo -= valor;
            destino1.depositar(metade); // chama depositar para respeitar o encapsulamento, facilitar manutenções futuras e reaproveitar código
            destino2.depositar(metade);
            cout << "Transferido: R$ " << metade << " para cada conta (" << destino1.numero << " e " << destino2.numero 
            << ") da conta " << numero << endl;
        }
    }
    // método exibirSaldo, mostra o saldo atual da conta
    void exibirSaldo(){
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }
    // método exibirInformações, mostra todas as informações da conta (Titular, CPF, número da conta e saldo)
    void exibirInformacoes(){
        cout << "Titular: " << titular.getNome() << ", CPF: " << titular.getCpf() << endl;
        cout << "Número da conta: " << numero << ", Saldo: R$ " << saldo << endl;
    }
};

int main() {
    // Criação dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibição dos saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
