# Leaf Black — especificação do Randomizer

**Estado:** especificação técnica; ainda não integrado ao motor FireRed.

## Objetivo

Adicionar um Randomizer reproduzível à hack, com configurações selecionáveis antes de iniciar uma nova aventura. O Randomizer não deve alterar a ROM-base original nem misturar dados entre revisões.

## Modos

- **Iniciais:** sortear entre espécies disponíveis, mantendo três escolhas distintas quando possível.
- **Encontros selvagens:** randomizar por tabela de encontro e área; opção de manter níveis e raridade aproximados.
- **Treinadores:** trocar espécies mantendo a quantidade de Pokémon e uma faixa de nível semelhante; chefes e rivais podem usar regras próprias.
- **Habilidades:** sortear entre habilidades válidas para cada espécie, respeitando habilidades especiais e exceções definidas pelo projeto.
- **Golpes:** randomizar learnsets ou golpes de equipes de treinadores com validação de tipo, categoria e disponibilidade; evitar conjuntos vazios ou movimentos inválidos.
- **Semente (seed):** aceitar uma seed numérica/textual para reproduzir exatamente a mesma configuração.
- **Restrições:** modo seguro por padrão, evitando espécies/golpes não implementados, referências inválidas e softlocks de progressão.

## Arquitetura proposta

1. Criar uma configuração versionada com toggles, seed e regras de randomização.
2. Usar um PRNG determinístico; a mesma seed + versão de dados deve produzir os mesmos resultados.
3. Carregar tabelas de espécies, encontros, treinadores, habilidades e golpes a partir da base de código FireRed escolhida.
4. Randomizar em fase de geração/build, não durante cada batalha, para manter a ROM resultante estável.
5. Validar índices, espécies disponíveis, níveis, learnsets, referências de scripts e requisitos de progressão.
6. Registrar seed, opções e versão do randomizer em um arquivo de log para facilitar suporte e reprodução de bugs.
7. Construir uma ROM modificada a partir da base limpa e gerar um patch diferencial IPS/BPS. Nunca incluir a ROM comercial no repositório.

## Testes obrigatórios

- Mesma seed e mesmas opções geram os mesmos dados.
- Seeds diferentes normalmente geram resultados diferentes.
- Nenhuma tabela aponta para espécie, habilidade ou golpe inexistente.
- Equipes de treinadores e encontros mantêm limites válidos.
- A campanha pode ser concluída sem bloqueios de progressão causados pelo randomizer.
- Patch aplica somente à revisão de ROM documentada e passa por testes em emulador.

## Bloqueios atuais

O repositório contém um protótipo GBA independente, não uma base FireRed integrada. Portanto, esta especificação não significa que o Randomizer já funcione no jogo. A implementação depende de selecionar e configurar uma base de código FireRed compatível, compilar o motor e então conectar estas regras aos dados reais.
