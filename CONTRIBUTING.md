# Contributing

This file is in WIP

## License and Copyright Attribution

When you open a Pull Request to the project, you agree to license your code under the [GNU GENERAL PUBLIC LICENSE 3](LICENSE).

Be sure to have the right to do that (if you are a professional, ask your company)!

If you include code from another project, please mention it in the Pull Request description and credit the original author.

## Getting started

<!-- Work in progress -->

### Requirements

### Pre-commit

### Tests

## Managment

### Branches

#### Features

Your feature branch sould respect this spec:

```
<topic>/description-formated-like-this
```

The `<topic>` should as possible matchs to these:

- `refacto`
- `feature`
- `refacto`
- `tests` this should be exception
- `adr`
- `doc`
- `fix`

### Commit Messages

The commit message must follow this nomenclature: using [gitmoji](https://gitmoji.dev/) for topic selection

With issues:

```
[<topic>][#<issue id>] <Title>
```

Or with pull request:

```
[<topic>][!<pull request id>] <Title>

```

Here a `~/.gitmessage` to help you:

```gitmessage
[][#] Replace me

# documentation:

# [<topic>][#<issue id>] <Title>

# [<topic>][!<pull request id>] <Title>

#

# <type>: must respect gitmoji convention:https://gitmoji.carloscuesta.me/

# e.g:

# [ubiback/web#12][refacto] Refacto my banana

```

## Architecture 👷

<!-- Work in progress -->

Our architecture is following these principes

- `DDD`
- `Exagonal architecture`
- `SOLID`
- `Design pattens`
- `BDD` (and `TDD` if you can)

## Architecture decision records

https://adr.github.io/

The spec is written in Markdown, compatible with [Mmark](https://mmark.miek.nl/).
It is then converted in the [the "xml2rfc" Version 3 Vocabulary](https://tools.ietf.org/html/rfc7991).

To contribute to the architecture decision :

- Make your changes
- [Download Mmark](https://github.com/mmarkdown/mmark/releases)
- [Download `xml2rfc` using pip](https://pypi.org/project/xml2rfc/): `pip install xml2rfc`
- Format the Markdown file: `mmark -markdown -w spec/mercure.md`
- Generate the XML file: `mmark spec/mercure.md > spec/mercure.xml`
- Validate the generated XML file and generate the text file: `xml2rfc --text --v3 spec/mercure.xml`
- Remove non-ASCII characters from the generated `mercure.txt` file (example: K**é**vin)
