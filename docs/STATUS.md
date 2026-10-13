# Leaf Black — status real

## Implementado no repositório
- Protótipo GBA independente escrito em C com build automatizado por GitHub Actions.
- Seleção dos três iniciais originais: Fernling, Cindrake e Brookit.
- Tela de confirmação do inicial.
- Mapa de rota demonstrativo com movimento pelas setas.
- Encontro em áreas de grama, batalha simples por turnos, HP e contador de vitórias.
- Dados de design dos iniciais em `data/species.json`.
- Protótipo web com seleção, exploração ilustrativa e batalha de demonstração.

## Ainda não é a ROM hack de FireRed
- O binário `leafblack.gba` é um jogo GBA independente, não uma modificação de Pokémon FireRed.
- Ainda falta integrar o projeto a uma base de código compatível com FireRed USA 1.0.
- Faltam motor de FireRed modificado, mapas finais, história, treinadores, encontros completos, inventário, salvamento, sprites finais e testes em emulador.
- Ainda não existe patch IPS/BPS final testado.

## Próximos passos
1. Confirmar a compatibilidade da base de código com a versão exata da ROM alvo.
2. Fazer build limpo em nuvem sem armazenar a ROM comercial no repositório.
3. Integrar uma mudança de jogo por vez e validar em emulador.
4. Completar conteúdo, eventos, batalhas, evoluções, itens e salvamento.
5. Criar e testar um patch diferencial usando a cópia limpa da ROM do usuário.
6. Publicar somente o patch e os arquivos originais do projeto, nunca a ROM completa.

**Não declarar o hack completo até que um patch real tenha sido criado e testado com sucesso.**
