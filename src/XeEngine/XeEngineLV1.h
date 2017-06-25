#pragma once
#include "XeBase.h"
#include "XeSystem.h"
#include "XeMemory.h"
#include "XeString.h"
#include "XeFile.h"
#include "XeMath.h"
#include "XeColor.h"

/*
Il livello 1 dell'engine � costruito subito sopra il sistema operativo di destinazione.
Si occupa di interfacciarsi e semplificare le operazioni dei file e la gestione della memoria.
Praticamente ogni livello sovrastante si baser� sul livello 1. Il livello 0 � il sistema operativo di destinazione.

TODO:
XeFileSystem: si occupa di gestire un macrofile che conterr� tutti i file data del gioco in sola lettura.
*/