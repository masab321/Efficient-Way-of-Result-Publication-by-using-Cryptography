#include <bits/stdc++.h>
#include <themispp/secure_cell.hpp>
using namespace std;

class crypto
{
public:
    crypto() {}
    string base64_encode(const string &data)
    {
        static constexpr char sEncodingTable[] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '0', '1', '2', '3',
            '4', '5', '6', '7', '8', '9', '+', '/'};

        size_t in_len = data.size();
        size_t out_len = 4 * ((in_len + 2) / 3);
        string ret(out_len, '\0');
        size_t i;
        char *p = const_cast<char *>(ret.c_str());

        for (i = 0; i < in_len - 2; i += 3)
        {
            *p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
            *p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
            *p++ = sEncodingTable[((data[i + 1] & 0xF) << 2) | ((int)(data[i + 2] & 0xC0) >> 6)];
            *p++ = sEncodingTable[data[i + 2] & 0x3F];
        }
        if (i < in_len)
        {
            *p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
            if (i == (in_len - 1))
            {
                *p++ = sEncodingTable[((data[i] & 0x3) << 4)];
                *p++ = '=';
            }
            else
            {
                *p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
                *p++ = sEncodingTable[((data[i + 1] & 0xF) << 2)];
            }
            *p++ = '=';
        }

        return ret;
    }
    string base64_decode(const string &input)
    {
        string out;
        static constexpr unsigned char kDecodingTable[] = {
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
            64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
            64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};

        size_t in_len = input.size();
        if (in_len % 4 != 0)
            return "Input data size is not a multiple of 4";

        size_t out_len = in_len / 4 * 3;
        if (input[in_len - 1] == '=')
            out_len--;
        if (input[in_len - 2] == '=')
            out_len--;

        out.resize(out_len);

        for (size_t i = 0, j = 0; i < in_len;)
        {
            uint32_t a = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
            uint32_t b = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
            uint32_t c = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
            uint32_t d = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];

            uint32_t triple = (a << 3 * 6) + (b << 2 * 6) + (c << 1 * 6) + (d << 0 * 6);

            if (j < out_len)
                out[j++] = (triple >> 2 * 8) & 0xFF;
            if (j < out_len)
                out[j++] = (triple >> 1 * 8) & 0xFF;
            if (j < out_len)
                out[j++] = (triple >> 0 * 8) & 0xFF;
        }

        return out;
    }

    vector<uint8_t> string_to_uint8(const string &s)
    {
        vector<uint8_t> ret(s.begin(), s.end());
        return ret;
    }

    string uint8_to_string(vector<uint8_t> &u)
    {
        ostringstream ret;
        for (int i = 0; i < u.size(); i++)
            ret << u[i];
        return ret.str();
    }

    string encrypt(string pass, string msg)
    {
        auto cell = themispp::secure_cell_seal_with_passphrase(pass);
        vector<uint8_t> plaintext = string_to_uint8(msg);
        vector<uint8_t> encrypted = cell.encrypt(plaintext);
        string str = uint8_to_string(encrypted);
        string ret = base64_encode(str);
        return ret;
    }
    string decrypt(string pass, string encoded)
    {
        string ret;
        try
        {
            auto cell = themispp::secure_cell_seal_with_passphrase(pass);
            string decoded = base64_decode(encoded);
            vector<uint8_t> encrypted = string_to_uint8(decoded);
            vector<uint8_t> decrypted = cell.decrypt(encrypted);
            ret = uint8_to_string(decrypted);
            return ret;
        }
        catch (const themispp::exception_t &e)
        {
            // handle decryption failure
            return "failed";
        }
        return ret;
    }
};

//base64 encode decode function are taken from https://gist.github.com/tomykaira/f0fd86b6c73063283afe550bc5d77594
// string crypto::base64_encode(const string &data)
// {
//     static constexpr char sEncodingTable[] = {
//         'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
//         'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
//         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
//         'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
//         'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
//         'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
//         'w', 'x', 'y', 'z', '0', '1', '2', '3',
//         '4', '5', '6', '7', '8', '9', '+', '/'};

//     size_t in_len = data.size();
//     size_t out_len = 4 * ((in_len + 2) / 3);
//     string ret(out_len, '\0');
//     size_t i;
//     char *p = const_cast<char *>(ret.c_str());

//     for (i = 0; i < in_len - 2; i += 3)
//     {
//         *p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
//         *p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
//         *p++ = sEncodingTable[((data[i + 1] & 0xF) << 2) | ((int)(data[i + 2] & 0xC0) >> 6)];
//         *p++ = sEncodingTable[data[i + 2] & 0x3F];
//     }
//     if (i < in_len)
//     {
//         *p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
//         if (i == (in_len - 1))
//         {
//             *p++ = sEncodingTable[((data[i] & 0x3) << 4)];
//             *p++ = '=';
//         }
//         else
//         {
//             *p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
//             *p++ = sEncodingTable[((data[i + 1] & 0xF) << 2)];
//         }
//         *p++ = '=';
//     }

//     return ret;
// }

// string crypto::base64_decode(const string &input)
// {
//     string out;
//     static constexpr unsigned char kDecodingTable[] = {
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
//         52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
//         64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
//         15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
//         64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
//         41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
//         64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};

//     size_t in_len = input.size();
//     if (in_len % 4 != 0)
//         return "Input data size is not a multiple of 4";

//     size_t out_len = in_len / 4 * 3;
//     if (input[in_len - 1] == '=')
//         out_len--;
//     if (input[in_len - 2] == '=')
//         out_len--;

//     out.resize(out_len);

//     for (size_t i = 0, j = 0; i < in_len;)
//     {
//         uint32_t a = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
//         uint32_t b = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
//         uint32_t c = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
//         uint32_t d = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];

//         uint32_t triple = (a << 3 * 6) + (b << 2 * 6) + (c << 1 * 6) + (d << 0 * 6);

//         if (j < out_len)
//             out[j++] = (triple >> 2 * 8) & 0xFF;
//         if (j < out_len)
//             out[j++] = (triple >> 1 * 8) & 0xFF;
//         if (j < out_len)
//             out[j++] = (triple >> 0 * 8) & 0xFF;
//     }

//     return out;
// }

// int main(){

//     string plain = "its not important";
//     string pass = "drama";
//     crypto c = crypto();
//     string en = c.encrypt(pass, plain);
//     string dec = c.decrypt(pass, en);
//     cout << plain << endl;
//     cout << en << endl;
//     cout << dec << endl;

//     ofstream fout("cipher.txt");
//     fout << en;

// }