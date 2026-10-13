# Leaf Black — status real

## Build GBA mais recente
- GitHub Actions: **build concluído com sucesso** no commit `b9f4defeabfa15a7580b838ec68d88a342590d90`.
- Execução: https://github.com/tamojuntoy477-pixel/Leaf_black/actions/runs/38418123570
- Artefato gerado: `leaf-black-gba-prototype` (contém `leafblack.gba`, build de 7.320 bytes).
- Este artefato é um protótipo técnico e pequeno; sucesso de compilação não significa que a ROM hack de FireRed esteja pronta nem que o jogo tenha sido testado em emulador.

## Implementado no repositório
- Protótipo GBA independente escrito em C com build automatizado por GitHub Actions.
- Seleção dos três iniciais originais: Fernling, Cindrake e Brookit.
- Tela de confirmação do inicial.
- Mapa de rota demonstrativo com movimento pelas setas.
- Encontro em áreas de grama, batalha simples por turnos, HP e contador de vitórias.
- Ataque rápido e ataque especial na batalha.
- Dados de design dos iniciais em `data/species.json`.
- Protótipo web com seleção, exploração ilustrativa e batalha de demonstração.

## Ainda não é a ROM hack de FireRed
- O binário `leafblack.gba` é um jogo GBA independente, não uma modificação de Pokémon FireRed.
- A ROM enviada tem cabeçalho de jogo `BPRE`, versão 0 e tamanho de 16 MiB; isso, sozinho, não confirma que seja a revisão/base esperada nem que esteja compatível com uma base de descompilação.
- Ainda falta integrar o projeto a uma base de código compatível com a ROM alvo.
- Faltam motor de FireRed modificado, mapas finais, história, treinadores, encontros completos, inventário, salvamento, sprites finais e testes em emulador.
- Ainda não existe patch IPS/BPS final testado.

## Próximos passos
1. Confirmar a revisão exata da ROM alvo e sua compatibilidade com a base de código.
2. Fazer build limpo em nuvem sem armazenar a ROM comercial no repositório.
3. Integrar uma mudança de jogo por vez e validar em emulador.
4. Completar conteúdo, eventos, batalhas, evoluções, itens e salvamento.
5. Criar e testar um patch diferencial usando a cópia limpa da ROM do usuário.
6. Publicar somente o patch e os arquivos originais do projeto, nunca a ROM completa.

**Não declarar o hack completo até que um patch real tenha sido criado e testado com sucesso.**
