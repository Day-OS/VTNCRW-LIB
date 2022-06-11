# Visual Tiles Nicely Compacted - Reader/Writer LIB
## WORK IN PROGRESS
C++ Library for a created file format (primarily) for my Monitor project.
Yes, I know it is a strange name.

[[Video that shows "prototipo file" working]](https://cdn.discordapp.com/attachments/401071914346610688/925715321208320000/VID_20211228_232326.mp4)

I'm using [ImHEX](https://github.com/WerWolv/ImHex) for prototyping as seen in `filestructure/`.



Bitwise instead of Bytewise

Mudar as regras (no header) para usar o espaço apropriadamente, utilizando de bits para o espaço necessário devido.

Mudar a capacidade total (MÁXIMA, podendo e devendo ser menor) de cores que podem ser armazenadas em um arquivo VTNCI, sendo 2²*⁴ o necessário para todas as possíveis combinaçoes de 4 bytes.

Mudar o tamanho alocado de indice/endereço das cores no buffer. Ex: Uma imagem monocromática necessita somente, apenas, de 1 bit. Uma imagem com 3 ou mais cores necessita de 2 bits.
 



| Index   | Size | Text or value | Meaning |
| :------ | ---- | :------------ | :------ |
| 0x0 (0) | 5    | VTNCI         | Header  |
| 0x5 (0) | 1    | ( ?, ? )      | Sizes  |
