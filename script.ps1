for ($i=32;$i -ge 10;$i--) {
	if ($i%2 -eq 0){
		./othello.exe 1 $i >> resultados_parafichas_blancas.txt
	}
}