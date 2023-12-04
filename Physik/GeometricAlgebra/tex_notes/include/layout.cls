
%% -------------------------------
%% | Definition der LaTeX Klasse |
%% -------------------------------
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{include/layout}
\LoadClass[a4paper,11pt,titlepage]{scrreprt}

\usepackage[ngerman]{babel} % Unterstützung für die deutsche Sprache

%% ---------------------
%% | Design und Layout |
%% ---------------------
\usepackage{xcolor} % Farben
\definecolor{myblue}{rgb}{0, 0.34, 0.61} % Blau als Layout-Farbe definieren
\addtokomafont{chapter}{\color{myblue}} % Alle Kapitel blau einfärben

\usepackage{coffee4} % Kaffeefleck auf der Titelseite

\usepackage{geometry} % Seiten-Ränder anpassen
\geometry{a4paper,total={170mm,257mm},left=20mm,top=20mm,}

\addtolength{\topmargin}{.35in}
\addtolength{\textheight}{-.45in}

% Hyperlinks im Inhaltsverzeichnis
\usepackage{hyperref}
\hypersetup{
	raiselinks=true,
	linktoc=all,
	plainpages=false,
	allbordercolors=myblue, % Farbe der Link-Umrandung
	%colorlinks=true, % deaktiviert, entfernt die Umrandung und färbt die Links ein
	%linkcolor=myblue,
	%hidelinks=true, % deaktiviert, entfernt die Einfärbung von Links / Umrandung
}


%% -----------------------------
%% | Funktionsumfang erweitern |
%% -----------------------------
\usepackage[automark,markcase=upper]{scrlayer-scrpage} % Kopf- und Fußzeile anpassen
\usepackage{enumitem} % Customising the numbered lists
\usepackage{nameref} % reference the names of the sections
\usepackage[normalem]{ulem} % Dashed lines in appendix

% mathematische Symbole
\usepackage{amsmath}
\usepackage{amssymb}

\usepackage{subcaption} % captions für subfigures
\usepackage{pythontex} % Verwendung von Python-skripten um Plots zu erstellen
\usepackage{tikz}
\usepackage{pgfplots}
\pgfplotsset{compat=1.18}	% Verhindert, dass eine Warnung ausgespuckt wird
\usepackage{todonotes}

%\usepackage[pdftex]{graphicx} % Bilder einfügen, deaktiviert wegen einem "option clash" Problem
\usepackage{svg} % svg Dateien einbinden

%% -------------------------
%% | SIunitx Konfiguration |
%% -------------------------
\usepackage{siunitx}
\sisetup{output-decimal-marker={,}} % Dezimaltrenner
\sisetup{list-final-separator={ und }} % Letzter Separator nach Auflistungen ( 1, 2 und 3)
\sisetup{range-phrase={ bis }} % Range: 1,8 bis 2,7
\sisetup{locale=DE} % \cdot anstelle von \times

%% *** Ende der klassen-Definition ***
