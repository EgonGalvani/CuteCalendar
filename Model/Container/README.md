# Container 
Il container considerato è un albero di intervalli. Per l'implementazione è stato usato un albero rosso-nero aumentato. In particolare ogni nodo presenta: estremo sinistro, estremo destro e il massimo estremo presente nell'albero in sè radicato.

# Complessità container 
| Funzione | Complessità |
| --- | --- |
| inserimento | O(log N) |
| cancellazione | O(log N) |
| ricerca di un'intersezione | O(log N) |
| ricerca di tutte le intersezioni | O(k logN), dove k è il numero di intervalli che intersecano quello dato |
| iteratori | O(log N) |

# Considerazioni 
- E' possibile raggiungere un tempo costante negli iteratori aggiungendo uno stack al loro interno 
- Per il momento l'abero gestisce solo intervalli del tipo [a, b] 
