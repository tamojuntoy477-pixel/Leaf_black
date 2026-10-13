# Leaf Black — status real

## Implementado no repositório
- Protótipo GBA independente com seleção de três iniciais.
- Tela de confirmação do inicial e retorno à seleção.
- Compilação automática via GitHub Actions.
- Protótipo web com seleção, exploração ilustrativa e batalha de demonstração.
- Dados de design originais dos iniciais em `data/species.json`.

## Ainda não implementado
- Integração com a base de código de Pokémon FireRed USA 1.0.
- Mudanças reais no motor de FireRed.
- Mapas GBA jogáveis, eventos, treinadores, encontros, inventário e salvamento.
- Evoluções funcionais e sprites originais dentro do jogo.
- Testes de regressão em emulador e patch IPS/BPS final.

## Caminho de conclusão
1. Selecionar e documentar uma base decompilada compatível com a ROM alvo.
2. Fazer build limpo na nuvem sem armazenar a ROM original no repositório.
3. Implementar uma primeira mudança pequena e validar no emulador.
4. Adicionar conteúdo em etapas: inicial, rota inicial, encontro, batalha, cura e salvamento.
5. Gerar um patch diferencial a partir de uma base legalmente obtida e validar o patch com uma cópia limpa da ROM do usuário.
6. Publicar somente patch e arquivos originais do projeto, nunca a ROM completa.

**Não declarar o hack completo até que o patch tenha sido criado e testado com sucesso.**
