# feta - a typo detector in Greek text
`feta` is typographical error detection software for
text written in the Modern Greek language.

## How does it work?
The software uses an algorithm for the precise splitting
of words in syllables, based on the grammatical rules of the Modern Greek language.
Then, it uses those syllables to determine whether the word needs accent or not.
Because of this design, the program cannot detect spelling mistakes, only small typos.

## Compilation
```
sudo apt-get install libncurses-dev
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make
```

## Different executables
- `feta-check`

    The main executable file. It takes as the only argument a text file and prints out a list of typos
    that where detected.

    ```

    ./feta-check <text file path>
    ```

- `feta-count`

    Does the word splitting in syllables. It takes as the only parameter a word (in the Greek language)
    and outputs its split form.


    ```
    ./feta-count <word>
    ```

- `feta-test`

    Tests the `feta-count` and estimates its accuracy.
    It takes as the only parameter a text file with this format:
    ```
    <word> <split word in syllables>
    λέξη λέ-ξη
    συλλαβισμός συλ-λα-βι-σμός
    ```
    Checks if the output of the program is correct for
    every word in the file.

## Types of mistakes
- `excess accute accent`

    When a word has more than one accute accent (when that is not needed) or when it has one accent
    when that is also not needed (e.g. the word is monosyllabic.).
    e.g.
    ```
    Mistake: excess accute accent
        In word γιά at position 360
    Mistake: excess accute accent
        In word κάλήμέρά at position 89
    ```

- `no accute accent although it's needed`

    When a word is missing its accent:
    ```
    Mistake: no accute accent although it's needed
        In word καλημερα at position 89
    ```

## Software license
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 

## Why the name?
Idk, I guess because feta is a mainly a Greek cheese and also because it's kinda funny giving the software a name taken from food.