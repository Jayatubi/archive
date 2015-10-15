set nocompatible

" Plugins
call plug#begin('~/.vim/plugged')

Plug 'scrooloose/nerdtree'
Plug 'Valloric/YouCompleteMe'
Plug 'powerline/powerline'
Plug 'kien/ctrlp.vim'

call plug#end()

" Configs
syntax on
set showcmd
set hlsearch
set number
set expandtab
set smarttab
set tabstop=4
set softtabstop=4
set shiftwidth=4
set autoindent
set ruler
set laststatus=2
set showtabline=2
set noshowmode
set encoding=utf-8
set t_Co=256

" PowerLine
set rtp+=~/Library/Python/2.7/lib/python/site-packages/powerline/bindings/vim
let g:Powerline_symbols = 'fancy'

" NERDTree
let g:NERDTreeMapPreview="<F4>"
let g:NERDTreeMapActivateNode="<F3>"

map <F5> :NERDTreeToggle<CR>
map <F3> :NERDTreeFind<CR>

autocmd VimEnter * if !argc() | NERDTree | endif
autocmd BufEnter * if (winnr("$") == 1 && exists("b:NERDTreeType") && b:NERDTreeType == "primary") | q | endif
