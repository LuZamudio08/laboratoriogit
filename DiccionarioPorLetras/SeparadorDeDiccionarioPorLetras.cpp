//hecho con IA
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

// Detecta la letra inicial en UTF-8 (incluyendo tildes y ñ/Ñ)
std::string obtenerLetraInicial(const std::string& palabra) {
    for (size_t i = 0; i < palabra.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(palabra[i]);

        // Letras ASCII estándar (A-Z, a-z)
        if (std::isalpha(c)) {
            char upper = static_cast<char>(std::toupper(c));
            return std::string(1, upper);
        }

        // Caracteres UTF-8 de 2 bytes (tildes y Ñ/ñ empiezan con 0xC3)
        if (c == 0xC3 && i + 1 < palabra.size()) {
            unsigned char next = static_cast<unsigned char>(palabra[i + 1]);
            // á, é, í, ó, ú, ü y mayúsculas Á, É, Í, Ó, Ú, Ü
            if (next == 0xA1 || next == 0x81) return "A";
            if (next == 0xA9 || next == 0x89) return "E";
            if (next == 0xAD || next == 0x8D) return "I";
            if (next == 0xB3 || next == 0x93) return "O";
            if (next == 0xBA || next == 0x9A || next == 0xBC || next == 0x9C) return "U";
            // ñ (0xB1) o Ñ (0x91)
            if (next == 0xB1 || next == 0x91) return "Ñ";
            ++i; // Saltar el segundo byte
        }
    }
    return "";
}

int main() {
    std::ifstream entrada("Diccionario-espanol.txt");
    if (!entrada.is_open()) {
        std::cerr << "Error: No se pudo abrir Diccionario-espanol.txt\n";
        return 1;
    }

    std::vector<std::string> alfabeto = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
        "N", "Ñ", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
    };

    std::map<std::string, std::vector<std::string>> grupos;
    std::string linea;

    while (std::getline(entrada, linea)) {
        // Eliminar retorno de carro (\r) si existe
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }
        if (linea.empty()) continue;

        std::string letra = obtenerLetraInicial(linea);
        if (!letra.empty()) {
            grupos[letra].push_back(linea);
        }
    }
    entrada.close();

    // Generar los 27 archivos CSV separados por comas
    for (const auto& letra : alfabeto) {
        std::string nombreArchivo = "letra_" + letra + ".csv";
        std::ofstream salida(nombreArchivo, std::ios::binary);

        // Escribir BOM UTF-8 para compatibilidad directa con Excel
        salida << "\xEF\xBB\xBF";

        const auto& palabras = grupos[letra];
        for (size_t i = 0; i < palabras.size(); ++i) {
            if (palabras[i].find(',') != std::string::npos) {
                salida << "\"" << palabras[i] << "\"";
            } else {
                salida << palabras[i];
            }
            if (i + 1 < palabras.size()) {
                salida << ",";
            }
        }
        salida.close();
        std::cout << nombreArchivo << ": " << palabras.size() << " palabras\n";
    }

    return 0;
}