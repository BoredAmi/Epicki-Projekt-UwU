
Ze względu na niedocenienie ilości zadań, jakie trzeba było wykonać, nie udało nam się w pełni zintegrować wszystkich elementów gry w taki sposób, aby były one poprawnie wyświetlane na ekranie. Mimo to, poszczególne komponenty gry, takie jak generowanie terenu, ruch zwierząt, interakcje gracza i cykl dnia, są zaimplementowane i mogą być dalej rozwijane w przyszłości.

main.cpp: Punkt wejścia do gry, ustawia okno i obsługuje główną pętlę gry.
critter.cpp / critter.h: Definiuje zwierzęta i ich zachowania.
cycle_day.cpp / cycle_day.h: Zarządza cyklem dnia i nocy oraz związanymi wydarzeniami.
entity.cpp / entity.h: Klasa bazowa dla wszystkich postaci w grze.
perlin.cpp / perlin.h: Implementacja Simplex Noise do generowania terenu.
