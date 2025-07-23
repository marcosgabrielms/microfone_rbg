// Se UTILS_H não estiver definido, continua
#ifndef UTILS_H 
#define UTILS_H // Define UTILS_H para evitar inclusões múltiplas deste header

//Limites de som (Ajuste conforme o ambiente)
extern float LIMITE_SOM_BAIXO;
extern float LIMITE_SOM_ALTO;

void calibrar_limites_automaticamente(int duracao_ms);

#endif // Fim da diretiva de inclusão condicional UTILS_H