================================================================================
    MICROSOFT FOUNDATION CLASS-BIBLIOTHEK: DirectX_Sound-Projektübersicht
===============================================================================

Diese DirectX_Sound-Anwendung wurde vom Anwendungs-Assistenten für Sie erstellt. Diese Anwendung zeigt nicht nur die Grundlagen der Verwendung von Microsoft Foundation Classes, sondern dient auch als Ausgangspunkt für das Schreiben Ihrer Anwendung.

Diese Datei bietet eine Übersicht über den Inhalt der einzelnen Dateien, aus
denen Ihre DirectX_Sound-Anwendung besteht.

DirectX_Sound.vcxproj
    Dies ist die Hauptprojektdatei für VC++-Projekte, die mit dem Anwendungs-Assistenten generiert werden. Sie enthält Informationen über die Version von Visual C++, mit der die Datei generiert wurde, sowie über die Plattformen, Konfigurationen und Projektfunktionen, die im Anwendungs-Assistenten ausgewählt wurden.

DirectX_Sound.vcxproj.filters
    Dies ist die Filterdatei für VC++-Projekte, die mithilfe eines Anwendungs-Assistenten erstellt werden. Sie enthält Informationen über die Zuordnung zwischen den Dateien im Projekt und den Filtern. Diese Zuordnung wird in der IDE zur Darstellung der Gruppierung von Dateien mit ähnlichen Erweiterungen unter einem bestimmten Knoten verwendet (z. B. sind CPP-Dateien dem Filter "Quelldateien" zugeordnet).

DirectX_Sound.h
    Dies ist die Hauptheaderdatei für die Anwendung.
    Sie enthält andere projektspezifische Header (einschließlich Resource.h) und deklariert die CDirectX_SoundApp-Anwendungsklasse.

DirectX_Sound.cpp
    Dies ist die wichtigste Anwendungsquelldatei, die die Anwendungsklasse CDirectX_SoundApp enthält.

DirectX_Sound.rc
    Dies ist eine Auflistung aller vom Programm verwendeten Microsoft Windows-Ressourcen. Sie enthält die Symbole, Bitmaps und Cursor, die im Unterverzeichnis "RES" gespeichert werden. Diese Datei kann direkt in Microsoft Visual C++ bearbeitet werden. Ihre Projektressourcen befinden sich in 1031.

res\DirectX_Sound.ico
    Dies ist eine Symboldatei, die als Anwendungssymbol verwendet wird. Dieses Symbol ist in der Hauptressourcendatei DirectX_Sound.rc enthalten.

res\DirectX_Sound.rc2
    Diese Datei enthält Ressourcen, die nicht von Microsoft Visual C++ bearbeitet werden. Sie sollten alle Ressourcen, die nicht mit dem Ressourcen-Editor bearbeitet werden können, in dieser Datei platzieren.


/////////////////////////////////////////////////////////////////////////////

Der Anwendungs-Assistent erstellt eine Dialogfeldklasse:

DirectX_SoundDlg.h, DirectX_SoundDlg.cpp - das Dialogfeld
    Diese Dateien enthalten Ihre CDirectX_SoundDlg-Klasse. Diese Klasse definiert das Verhalten des Hauptdialogfelds der Anwendung. Die Vorlage für das Dialogfeld befindet sich in DirectX_Sound.rc und kann in Microsoft Visual C++ bearbeitet werden.

/////////////////////////////////////////////////////////////////////////////

Andere Standarddateien:

StdAfx.h, StdAfx.cpp
    Mit diesen Dateien werden eine vorkompilierte Headerdatei (PCH) mit dem Namen DirectX_Sound.pch und eine vorkompilierte Typendatei mit dem Namen StdAfx.obj erstellt.

Resource.h
    Dies ist die Standardheaderdatei, die neue Ressourcen-IDs definiert. Die Datei wird mit Microsoft Visual C++ gelesen und aktualisiert.

/////////////////////////////////////////////////////////////////////////////

Weitere Hinweise:

Der Anwendungs-Assistent weist Sie mit "TODO:"-Kommentaren auf Teile des Quellcodes hin, die Sie ergänzen oder anpassen sollten.

Wenn Ihre Anwendung MFC in einer gemeinsam genutzten DLL verwendet, müssen die MFC-DLLs mitverteilt werden. Wenn Ihre Anwendung eine andere Sprache als Systemsprache verwendet, müssen auch die entsprechende mfc110XXX.DLL für die lokalisierten Ressourcen mitverteilt werden.
Weitere Informationen zu diesen beiden Themen finden Sie im Abschnitt zur Neuverteilung von Visual C++-Anwendungen in der MSDN-Dokumentation.

/////////////////////////////////////////////////////////////////////////////
