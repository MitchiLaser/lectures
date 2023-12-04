
%% -------------------------------
%% | Definition der LaTeX Klasse |
%% -------------------------------
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{include/layout}
\LoadClass[twoside=false]{scrbook}

\setkomafont{author}{\scshape}
\usepackage{bookman}
\KOMAoptions{DIV=last}

%% ----------------------
%% | Verwendete Klassen |
%% ----------------------
\usepackage[ngerman]{babel}
\usepackage{xcolor} % Farben
\usepackage{hyperref} % Links und Hyperlinks
\hypersetup{
	raiselinks=true,
	linktoc=all,
	plainpages=false,
}
% mathematische Symbole
\usepackage{amsmath}
\usepackage{amssymb}
\usepackage{subcaption}
\usepackage{pythontex}
\usepackage{pgfplots}
\pgfplotsset{compat=1.18} % verhindern, dass eine Warnung ausgespuckt wird
\usepackage{todonotes} % TODO: entfernen, wenn alle TODOs erledigt sind
\usepackage{svg} % SVG Dateien einbinden
\usepackage{csquotes}

%% -------------------------
%% | SIunitx Konfiguration |
%% -------------------------
\usepackage{siunitx}
\sisetup{output-decimal-marker={,}} % Dezimaltrenner
\sisetup{list-final-separator={ und }} % Letzter Separator nach Auflistungen ( 1, 2 und 3)
\sisetup{range-phrase={ bis }} % Range: 1,8 bis 2,7
\sisetup{locale=DE} % \cdot anstelle von \times
