# CMakeList.txt: Projekt CMake pro interaktivni_testy, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

project ("interaktivni_testy")

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (interaktivni_testy "main.cpp"  "test.cpp" "test.h" "user.h" "user.cpp" "statistics.cpp" "statistics.h" "headers.h")

# TODO: V případě potřeby přidejte testy a cíle instalace.
