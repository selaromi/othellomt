for ($i=31;$i -ge 29;$i--) {
	if ($i%2 -ne 0){
		./othello.exe 1 $i >> resultados.txt
	}
}