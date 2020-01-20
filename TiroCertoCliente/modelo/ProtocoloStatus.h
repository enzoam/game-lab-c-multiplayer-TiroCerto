/*
 * Status via UDP
 *
 * Protocolo do servidor UDP
 *
 * Uso: A cada X segundos envia um broadcast avisando que o servico
 * esta disponivel no endereco e Porta configurados
 */
#ifndef PROTOCOLOSTATUS_H_INCLUDED
#define PROTOCOLOSTATUS_H_INCLUDED

#include <string>

struct ExistenciaInfo{
    std::string ip;
    std::string porta;
    int qtdeConectados;
    std::string nome;
}

#endif // PROTOCOLOSTATUS_H_INCLUDED