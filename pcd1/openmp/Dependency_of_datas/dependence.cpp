/* 5. Considere o seguinte laço:
a[0] = 0;
for ( i = 1; i < n ; i++)
a[i] = a[i-1] + i;
Há claramente uma dependência no laço já que o valor de a[i] não pode ser calculado
sem o valor de a[i-1]. Sugira uma maneira de eliminar essa dependência e paralelizar
o laço. */