# Desenvolver Leaf Black usando apenas Android

É possível acompanhar o projeto e editar arquivos pelo navegador do Android. A compilação GBA pode continuar a ser feita pelo GitHub Actions, na nuvem, sem instalar devkitARM no telefone.

## Fluxo pelo celular

1. Abra o repositório: https://github.com/tamojuntoy477-pixel/Leaf_black
2. Entre na conta GitHub e abra um arquivo de texto para editar, ou use o botão de edição no navegador.
3. Faça alterações pequenas e salve com um commit.
4. Abra a aba **Actions** para acompanhar a compilação automática.
5. Quando um artefato for publicado, abra a execução concluída, vá até **Artifacts** e baixe o ZIP.
6. Extraia o ZIP com o gerenciador de arquivos do Android e teste o arquivo `.gba` no emulador que você já usa.

## O que já está disponível

- Protótipo web em `index.html`.
- Protótipo GBA independente em `src/main.c`.
- Build automático GBA com GitHub Actions.
- Plano de design em `docs/HACK_COMPLETO.md`.

## Limite importante

O arquivo `leafblack.gba` atual é um protótipo independente; não é ainda um patch para FireRed. Para um hack verdadeiro precisamos integrar uma base de código decompilada compatível, desenvolver e testar mudanças, e por fim produzir um patch IPS/BPS. Não enviar a ROM comercial para o GitHub, nem colocá-la no repositório.

## Próxima etapa técnica

Escolher uma base de código decompilada compatível com FireRed USA 1.0. A compatibilidade deve ser confirmada na documentação da própria base antes de implementar alterações. Depois disso, preparar o fluxo de build na nuvem e começar por uma mudança pequena e verificável, antes de criar mapas e sistemas maiores.
