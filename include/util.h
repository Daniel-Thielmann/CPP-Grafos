#ifndef UTIL_H
#define UTIL_H

// Função inline para evitar múltiplas definições
inline double minValor(double a, double b, double c) {
    return (a < b && a < c) ? a : (b < c ? b : c);
}

#endif // UTIL_H
