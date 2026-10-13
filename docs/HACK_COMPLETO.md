# Leaf Black — plano do hack para FireRed USA 1.0

Este repositório **não distribui a ROM comercial** de Pokémon FireRed. O jogador usa sua própria cópia limpa e aplica localmente as modificações.

## Alvo técnico

- Jogo-base: Pokémon FireRed (USA), revisão 1.0.
- Saída de distribuição: patch IPS/BPS + código-fonte e assets originais do Leaf Black.
- O arquivo `.gba` de protótipo que já compilamos é um homebrew independente; ele ainda não modifica FireRed.
- Não misturar offsets de versões diferentes da ROM. Antes de aplicar qualquer patch, validar a revisão da ROM-base.

## Visão de conteúdo

### Região Verdelume
1. Vila inicial e laboratório.
2. Rota 1 e primeiro encontro com rival.
3. Cidade do primeiro ginásio.
4. Rotas, cavernas, missões e cidades adicionais.
5. Liga e pós-jogo.

### Iniciais originais
- Fernling — Planta
- Cindrake — Fogo
- Brookit — Água

Cada linha deve receber sprites frente/costas, ícone, cries quando houver suporte, stats, tipos, habilidades, learnsets, evoluções e entradas de Pokédex originais.

### Sistemas planejados
- História e eventos próprios.
- Treinadores e líderes de ginásio originais.
- Batalhas, experiência, evolução, itens e salvamento.
- Balanceamento e testes de progressão.
- Recursos adicionais só depois de a base principal estar estável.

## Etapas de desenvolvimento

1. **Base verificável:** configurar uma árvore de código-fonte compatível com FireRed USA 1.0 e documentar como compilar localmente.
2. **Primeiro patch pequeno:** mudar um texto e um evento controlado, compilar e comparar a ROM resultante com a ROM limpa.
3. **Loop jogável:** início, escolha de inicial, rival, rota e primeiro ginásio.
4. **Região e conteúdo:** mapas, scripts, treinadores, encontros e itens.
5. **Criaturas:** adicionar os monstros originais com assets próprios e dados consistentes.
6. **Teste e lançamento:** validar em emuladores e hardware compatível; publicar somente patch, fontes e assets que possamos distribuir.

## Para quem está com a ROM no Android

Não envie nem publique a ROM comercial. O fluxo recomendado é fazer o desenvolvimento num computador com a base de código e ferramentas apropriadas, usando sua ROM limpa apenas para a validação local. Para preparar o primeiro patch real, precisamos escolher uma base de código FireRed compatível e manter a revisão USA 1.0 fixa.

## Critério para chamar de “hack completo”

Só declarar completo quando a história principal puder ser terminada, os mapas/eventos não tiverem bloqueios conhecidos, os sistemas principais funcionarem, o patch aplicar numa ROM-base validada e os testes de emulador passarem. Até lá, os artefatos são versões de desenvolvimento.
