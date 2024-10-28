#include <iostream>
#include <vector>

using namespace std;

// Функция для нахождения НОД
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для нахождения мультипликативной обратной
int modinv(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Если обратное не найдено
}

// Функция генерации ключей RSA
void rsa_keygen(int p, int q, int& e, int& d, int& n, int& phi) {
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Выбор e
    e = 3;
    while (gcd(e, phi) != 1) {
        e += 2;
    }

    // Вычисление d
    d = modinv(e, phi);
}

// Функция для вычисления (base^exp) % mod
int modular_pow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod; // Для больших base

    while (exp > 0) {
        // Если exp нечетное, умножаем base с результатом
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        // exp должно быть четным теперь
        exp = exp >> 1; // Делим exp на 2
        base = (base * base) % mod; // Умножаем base на base
    }
    return result;
}

// Функция для шифрования сообщения
vector<int> rsa_encrypt(const string& message, int e, int n) {
    vector<int> encrypted;
    for (char ch : message) {
        int encrypted_char = modular_pow(static_cast<int>(ch), e, n);
        encrypted.push_back(encrypted_char);
    }
    return encrypted;
}

// Функция для расшифрования сообщения
string rsa_decrypt(const vector<int>& encrypted_message, int d, int n) {
    string decrypted;
    for (int enc_char : encrypted_message) {
        char decrypted_char = static_cast<char>(modular_pow(enc_char, d, n));
        decrypted += decrypted_char;
    }
    return decrypted;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Параметры
    int p = 7;
    int q = 13;
    string message = "ALPHA";

    // Генерация ключей
    int e, d, n, phi;
    rsa_keygen(p, q, e, d, n, phi);

    // Шифрование
    vector<int> encrypted_message = rsa_encrypt(message, e, n);

    // Расшифрование
    string decrypted_message = rsa_decrypt(encrypted_message, d, n);

    // Вывод результатов
    cout << "Открытый ключ (e, n): (" << e << ", " << n << ")\n";
    cout << "Закрытый ключ (d, n): (" << d << ", " << n << ")\n";
    cout << "φ(n): " << phi << "\n";
    cout << "Исходное сообщение: " << message << "\n";
    cout << "Зашифрованное сообщение: ";
    for (int enc : encrypted_message) {
        cout << enc << " ";
    }
    cout << "\nРасшифрованное сообщение: " << decrypted_message << endl;

    return 0;
}
