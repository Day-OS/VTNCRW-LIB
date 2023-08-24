# Visual Sequence File - Reader/Writer LIB
## WORK IN PROGRESS
Rust Library for a custom animated image file format that I created for my a fun "TV Head" cosplay project. It is also the project that I'm gonna be using for my undergraduate thesis.
Yes, I know it is a strange name, it will probably be changed in the future.

[[Video that shows "prototipo file" working]](https://cdn.discordapp.com/attachments/401071914346610688/925715321208320000/VID_20211228_232326.mp4) (old C++ Code)


## Some of the features the file have:
- Pixels are stored in a Color table called Palletes, just like gif files.
- The way of indexing a color from a color table changes depending on how many colors there are. So if the pallete contains only 2 colors, indexes will be stored in 1 bit, if it contains 4 colors, it will be stored in 2 bits. it will increase bit by bit, like: 3 bits, 4 bits, 5 bits, 6 bits... 1 byte and 2 bits, it just goes until it hits 4 bytes, then it stops. In this way it will be guaranteed it will only spend the necessary.


# FILE STRUCTURE
<img src="https://github.com/Day-OS/VTNCRW-LIB/blob/main/filestructure/onepixelheight.gif?raw=true" width="50%" style="image-rendering: pixelated;">

```js
//This is a RON representation of how the animated file works, THIS HAS NO OPTIMIZATION and it is just to give an idea of how it will be made

File(
    header: "VSF"
    width: 21,
    height: 1,
    // If this is true then "frames" will be an array of struct Frame, when its not it will have just one element.
    is_animated: true,
    // If this is true, then a pixel will take 4 bytes instead of only 3 bytes.
    has_alpha_channel: true,
    palettes: [
        //In this case the amount of colors is SO small it only contains 1 pallete and 4 colors.
        Palette{
            //As there is only 4 different colours there's no need to spend more than 2 bits for each index.
            //stored in a 5 bit space as this represent the quantity of bits in a 4 byte space (32).
            //https://en.wikipedia.org/wiki/Color_depth
            bit_depth: 0b10 // as there will always be a color, 0b0 must represent 1 instead of 0.
            colors: [
                Color{r: 0xFF, g: 0x00, b: 0x95, a: 0xFF},
                Color{r: 0x00, g: 0xB9, b: 0xF2, a: 0xFF},
                Color{r: 0xFA, g: 0xD5, b: 0x00, a: 0xFF},
                Color{r: 0x00, g: 0x00, b: 0x00, a: 0x00}
            ]
        }
    ]
    frames:[
        Frame{
            //how many times the height and the width is divided. The size of the chunk.
            chunk_subdivision: 1
            //In this case the image is SO small it only contains 1 chunk.
            chunks: [
                Chunk{
                  pallet_id : 0
                  pixels: [0b00, 0b01, 0b10, 0b11, 
                  0b00, 0b01, 0b10, 0b11, 
                  0b00, 0b01, 0b10, 0b11, 
                  0b00, 0b01, 0b10, 0b11, 
                  0b00] //[0,1,2,3]
                }
            ], 
            //The delay is in a hundreth of a second
            delay_frame_end: 100
        },
        Frame{
            chunk_subdivision: 1
            chunks: [
                Chunk{
                  pallet_id : 0
                  pixels: [0b01, 0b10, 0b11, 0b00,
                  0b01, 0b10, 0b11, 0b00,
                  0b01, 0b10, 0b11, 0b00,
                  0b01, 0b10, 0b11, 0b00,
                  0b01] //[1,2,3,0]
                }
            ], 
            delay_frame_end: 100
        },
        Frame{
            chunk_subdivision: 1
            chunks: [
                Chunk{
                  pallet_id : 0
                  pixels: [0b10, 0b11, 0b00, 0b01,
                  0b10, 0b11, 0b00, 0b01,
                  0b10, 0b11, 0b00, 0b01,
                  0b10, 0b11, 0b00, 0b01,
                  0b10] //[2,3,0,1]
                }
            ], 
            delay_frame_end: 100
        },
        Frame{
            chunk_subdivision: 1
            chunks: [
                Chunk{
                  pallet_id : 0
                  pixels: [0b11, 0b00, 0b01, 0b10,
                  0b11, 0b00, 0b01, 0b10,
                  0b11, 0b00, 0b01, 0b10,
                  0b11, 0b00, 0b01, 0b10,
                  0b11] //[3,0,1,2]
                }
            ],
            delay_frame_end: 100
        }
    ]
)
```
**This is just an example it might be changed in the future!!!**

<img src="https://github.com/Day-OS/VTNCRW-LIB/blob/main/filestructure/onepixelheight.png?raw=true" width="50%" style="image-rendering: pixelated;">


```js
//This is a RON representation of how the still imageworks, THIS ONE HAS BETTER DETAILS

//same as QOI Run! If the current pixel is the same as the before it will check every pixel in front of it to check if it is still the same. Then it will register how much times it repeated
//RUN(times_repeated)
//LZSS(OFFSET, LENGTH)
//It will copy the last pixel and change its value according to the specified rules.
//DIFF(difference_red, difference_green, difference_blue)
//HASH(Index) //THIS NEEDS a way to put them in an array in a fastest way!!!

File(
    header: "VSF"
    width: 0x0015,
    height: 0x0001,
    is_animated: false,
    has_alpha_channel: true,
    palettes_size: 0b0001
    palettes: [
        Palette{
            bit_depth: 0b10
            colors: [
                Color{r: 0xFF, g: 0x00, b: 0x95, a: 0xFF},
                Color{r: 0x00, g: 0xB9, b: 0xF2, a: 0xFF},
                Color{r: 0xFA, g: 0xD5, b: 0x00, a: 0xFF},
                Color{r: 0x00, g: 0x00, b: 0x00, a: 0x00}
            ]
        }
    ]
    frames:
        Single_Frame{
            chunk_subdivision: 1
            chunks: [
                Chunk{
                  pallet_id : 0
                  pixels: [Hash(0b11), Hash(0b00), Hash(0b01), Hash(0b10),
                  LZSS(0100, 1101)]  //
                }
            ],
        }
)
```



## Main
<table>
    <thead>
        <tr>
            <th>Offset # (HEX)</th>
            <th>Byte Size</th>
            <th>Content</th>
            <th>Meaning </th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>0</td>
            <td>3</td>
            <td>56 53 46 (ASCII for VSF)</td>
            <td>Header</td>
        </tr>
        <tr>
            <td>5</td>
            <td>4</td>
            <td>
                <table>
                    <thead>  
                        <tr>  
                            <th>Width</th>  
                            <th>Height</th> 
                        </tr>  
                    </thead>  
                    <tbody>  
                        <tr>  
                            <td>2 Bytes</td>  
                            <td>2 Bytes</td>   
                        </tr>  
                    </tbody>
                </table>
            </td>
            <td>Screen Resolution</td>
        </tr>
    </tbody>
</table>


|5| 1 | <table><thead>  <tr>  <th>Bit</th>  <th>Meaning</th>  </tr>  </thead>  <tbody>  <tr>  <td>1 Bit</td>  <td>Is animated?</td>   </tr>  <tr>  <td>1 Bit</td>  <td>Has alpha channel?</td>   </tr> <tr>  <td>6 Bit</td>  <td>Palettes Size</td>   </tr> </tbody></table>|Global configuration

    


| Offset # (HEX)| Byte SIze | Content                     | Meaning  |
| :------       | :------   | --------------------------- |  :------ |
| 0             |    3      | 56 53 46 (ASCII for VSF )   | Header   | 
| 5    |4| <table><thead>  <tr>  <th>Width</th>  <th>Height</th>  </tr>  </thead>  <tbody>  <tr>  <td>2 Bytes</td>  <td>2 Bytes</td>   </tr>  </tbody></table>   | Screen Resolution         |
|5| 1 | <table><thead>  <tr>  <th>Bit</th>  <th>Meaning</th>  </tr>  </thead>  <tbody>  <tr>  <td>1 Bit</td>  <td>Is animated?</td>   </tr>  <tr>  <td>1 Bit</td>  <td>Has alpha channel?</td>   </tr> <tr>  <td>6 Bit</td>  <td>Palettes Size</td>   </tr> </tbody></table>|Global configuration

    
| 5 + ? + 4  | ??               | ??            | Overall |

## Chunk

This is repeated a lot throughout the file.




3 bit for color quantity

# VER ISSO AQUI DEPOIS. PRIORIDADE Nº1
# Como alcançar True color?
<img src=https://upload.wikimedia.org/wikipedia/commons/a/aa/SmallFullColourGIF.gif>



https://en.wikipedia.org/wiki/GIF#True_color

Existem alguns problemas com esse método:
- O número de chunks precisa ter o mesmo número de cores na paleta? R: Não, elas devem variar de forma independente, ou seja, algumas chunks podem ter mais ou menos cores independendo das outras.
- Como saber o número ideal de chunks em uma imagem qualquer? R: As chunks poderiam começar por um número pré-definido e se subdividirem em chunks menores caso o numero de cores em uma certa chunk exceda o limite de 65,535 cores (2 Bytes)
- Uma paleta de uma chunk deve repetir mais de uma vez em caso de repetição extrema? R:SIM! Paletas devem possuir seus proprios identificadores.

As paletas serão declaradas individualmente das chunks de exibição, pois dessa forma haverá garantia que todas as chunks terão acesso a todas as paletas de cores.

- As chunks são REALMENTE necessárias se a ideia é usar menos do que 4 bytes? R: Em partes, sim! pois uma foto pode haver MUUUITAS cores de um lado e poucas do outro lado


Inspiration:
- https://bitbeamcannon.com/nes-graphical-specs/
- https://en.wikipedia.org/wiki/GIF
- https://en.wikipedia.org/wiki/PNG
- https://www.youtube.com/watch?v=EFUYNoFRHQI (How PNG Works: Compromising Speed for Quality)
- https://en.wikipedia.org/wiki/QOI_(image_format)