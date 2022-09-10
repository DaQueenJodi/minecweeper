call coc#config('languageserver', {
            \ 'clangd': {
            \   "command": "${CLANGD}",
            \   "args": ["--background-index"],
            \   "rootPatterns": ["compile_flags.txt", "compile_commands.json", ".vim/", ".git/", ".hg/"],
            \   "filetypes": ["c", "cpp", "objc", "objcpp"]
            \ }
            \})
