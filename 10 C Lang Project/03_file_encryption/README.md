# File Encryption/Decryption Tool

## Description
A simple file encryption and decryption tool that uses XOR cipher with a fixed key to secure files. The tool can encrypt any type of file and decrypt files that were previously encrypted with the same tool. Since XOR encryption is symmetric, the same operation works for both encryption and decryption.

## Features
- File encryption using XOR cipher
- File decryption for previously encrypted files
- Support for any file type (text, binary, images, etc.)
- Error handling for file operations
- Simple menu-driven interface

## Standard Library Functions Used
- `stdio.h` - For input/output operations and file handling (`fopen`, `fclose`, `fread`, `fwrite`, `printf`, `scanf`)
- `stdlib.h` - For program termination (`exit`)
- `string.h` - For string manipulation (though not heavily used in this implementation)

## How XOR Encryption Works
XOR encryption is a symmetric encryption method where:
- Each byte of the input file is XORed with a key
- Applying the same XOR operation with the same key reverses the encryption
- The simplicity makes it fast but not suitable for high-security applications

## How to Compile and Run

### Compilation
```bash
gcc -o file_encrypt main.c
```

### Execution
```bash
./file_encrypt
```

On Windows:
```bash
file_encrypt.exe
```

## How to Use
1. Run the program
2. Select whether to encrypt or decrypt a file
3. Enter the input file name (the file you want to process)
4. Enter the output file name (where you want to save the result)
5. The operation will complete and you can choose to perform another operation or exit

## Sample Usage
To create a test file for encryption:
```bash
echo "This is a secret message!" > test.txt
```

Then run the program and:
1. Choose option 1 (Encrypt a file)
2. Enter "test.txt" as input file
3. Enter "encrypted.dat" as output file
4. The file will be encrypted

To decrypt:
1. Choose option 2 (Decrypt a file)
2. Enter "encrypted.dat" as input file
3. Enter "decrypted.txt" as output file
4. The file will be decrypted back to original content

## Security Note
This tool implements a basic XOR cipher with a fixed key, which is not secure for protecting sensitive data. It's intended for educational purposes to demonstrate:
- File I/O operations in C
- Bitwise operations
- Basic encryption concepts

For real-world applications, use industry-standard encryption algorithms like AES.