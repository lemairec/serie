#include "langage.hpp"


Langage & Langage::instance(){
    static Langage obj;
    return obj;
}


const std::string & Langage::getKey(const std::string & ref){
    Langage & l = instance();
    if(l.m_l == MyLangage_fr){
        auto i = l.m_fr.find(ref);
        if(i != l.m_fr.end()){
            return i->second;
        }
    }
    if(l.m_l == MyLangage_en){
        auto i = l.m_en.find(ref);
        if(i != l.m_en.end()){
            return i->second;
        }
    }
    if(l.m_l == MyLangage_de){
        auto i = l.m_de.find(ref);
        if(i != l.m_de.end()){
            return i->second;
        }
    }
    l.m_fr["ref"] = "$" + ref;
    return l.m_fr["ref"];
}

void Langage::setLangage(int i){
    Langage & l = instance();
    l.m_l = (MyLangage)i;
}

void Langage::setLangage(const std::string & s){
    Langage & l = instance();
    if(s == "FR"){
        l.m_l = MyLangage_fr;
    } else if(s == "EN"){
        l.m_l = MyLangage_en;
    } else if(s == "DE"){
        l.m_l = MyLangage_de;
    }
}


Langage::Langage(){
    m_fr["HOME_L1"] = "AVERTISSEMENT";
    m_fr["HOME_L2"] = "- L'activation du système de guidage peut causer des mouvements inattendu.";
    m_fr["HOME_L3"] = "- Désactiver le guidage et l'hydraulique pour tout intervention sur la machine.";
    m_fr["HOME_L4"] = "- Tout dégat matériel et humain est sous la responsabilité de l'opérateur.";
    m_fr["ACCEPT"] = "Accepter";

    m_fr["HOME_VERSION"] = "version ";

    m_fr["MAIN_3POINT"] = "3ème Point";
    m_fr["MAIN_NOT_ENGAGED"] = "non activé";
    m_fr["MAIN_POOR_QUALITY"] = "qualité faible";
    m_fr["MAIN_NOT_CONNECTED"] = "non connecté";
    m_fr["MAIN_UNKNOWN_ERROR"] = "erreur inconnue";
    m_fr["MAIN_SCORE_LOW"] = "score trop faible";
    m_fr["MAIN_TEMP"] = "translateur non calibré";
    m_fr["MAIN_CONTRAINT"] = "translateur contraint";
    m_fr["MAIN_VITESSE_LOW"] = "vitesse faible";
    m_fr["MAIN_JOYSTICK_LEFT"] = "joystick gauche";
    m_fr["MAIN_JOYSTICK_RIGHT"] = "joystick droite";
    m_fr["MAIN_JOYSTICK_AUTO"] = "joystick auto";
    
    

    m_fr["MAIN_CALC"] = "cal : ";
    m_fr["MAIN_SCORE"] = "score : ";
    m_fr["MAIN_DEPL"] = "depl : ";
    m_fr["MAIN_ANG"] = "angle : ";
    m_fr["MAIN_VITESSE"] = "vitesse : ";
    
    m_fr["PARAMS_TITLE"] = "Menu de paramétrage du translateur";
    m_fr["PARAMS_P1_BEGIN"] = "Vous allez commencer le paramétrage du translateur de la bineuse.";
    m_fr["PARAMS_P1_SECURITY"] = "Assurez vous de pouvoir bouger le translateur en toute sécurité.";

    m_fr["PARAMS_P2_TEST"] = "Tester le deplacement gauche droite.";
    m_fr["PARAMS_P2_INVERSE_QUESTION"] = "Faut-il les inverser?";
    m_fr["INVERSE"] = "Inverse relais";

    m_fr["PARAMS_P3_MAX_LEFT"] = "Déplacer le translateur au maximum vers la gauche.";
    m_fr["PARAMS_P4_MAX_RIGHT"] = "Déplacer le translateur au maximum vers la droite.";
    m_fr["PARAMS_P5_CENTER"] = "Recentrer le translateur.";

    m_fr["PARAMS_P6_MESURE"] = "Mesurer le deplacement total du translateur.";
    m_fr["PARAMS_P6_DEBATTEMENT_CM"] = "Débattement ( cm )" ;
    m_fr["PARAMS_P7_AGRESSIVITY"] = "Régler l'agressivité.";;
    m_fr["PARAMS_P7_PUT_MAX"] = "Augmenter l'agressivité au maximum, sans que la bineuse oscille.";
    m_fr["PARAMS_P7_AGRESS"] = "Agressivité p : ";
    m_fr["PARAMS_P7_TEST"] = "Vous pouvez tester le deplacement.";

    m_fr["RAPIDE_COEFF"] = "coeff : ";
    m_fr["RAPIDE_CONSTRASTE"] = "contraste : ";

    m_fr["RAPIDE_CAMERA"] = "camera";
    m_fr["RAPIDE_HAUTEUR"] = "hauteur (cm)";
    m_fr["RAPIDE_ANGLE"] = "angle (°)";
    m_fr["RAPIDE_CULTURE"] = "Culture";
    m_fr["RAPIDE_NB_RANGS"] = "nbr rangs";
    m_fr["RAPIDE_INTERRANG"] = "inter rang (cm)";
    m_fr["RAPIDE_EPAISSEUR"] = "epaisseur (cm)";
    m_fr["RAPIDE_SCORE_MIN"] = "score min";

    m_fr["RAPIDE_OFFSET"] = "offset";
    m_fr["RAPIDE_DISTANCE"] = "distance (cm)";
    m_fr["RAPIDE_DEVERS"] = "devers";
    m_fr["RAPIDE_DISTANCE_SOC"] = "distance soc (cm)";

    m_fr["NEXT"] = "Suivant";
    m_fr["OK"] = "Ok";
    m_fr["CANCEL"] = "Annuler";
    m_fr["END"] = "Fin";
    m_fr["LEFT"] = "Gauche";
    m_fr["RIGHT"] = "Droite";
    m_fr["MIDDLE"] = "Milieu";

    m_fr["PLANTS"] = "Plantes";
    m_fr["HYDRAULIQUE"] = "Hydraulique";
    m_fr["OPTIONS"] = "Option";
    m_fr["CLOSE"] = "Quitter";
    
    m_fr["OPT_GEN_TITLE"] = "Options générales";
    m_fr["OPT_AV_TITLE"] = "Avancé";
    m_fr["OPT_AV_TECHNICIEN"] = "Technicien";
    m_fr["OPT_AV_AVANCE"] = "Avancé";
    m_fr["OPT_AV_DEBUG"] = "Debug";
    m_fr["OPT_VITESSE"] = "Vitesse";
    m_fr["OPT_CONN_TITLE"] = "Connection";
    m_fr["OPT_CONN_CART"] = "Carte de controle ";
    m_fr["OPT_CAMERAS"] = "Caméra(s)";
    m_fr["OPT_CAMERA_NBR"] = "cameras : ";
    m_fr["OPT_CAMERA_1"] = "camera 1 :";
    m_fr["OPT_CAMERA_2"] = "camera 2 :";
    m_fr["OPT_CAMERA_AUTO"] = "auto camera";
    m_fr["OPT_TECHN_TITLE"] = "Option Technicien";
    m_fr["OPT_TECHN_FOCAL"] = "focal : ";
    m_fr["OPT_TECHN_MULTI_THREAD"] = "multi_thread";
    m_fr["OPT_TECHN_RESOLUTION"] = "resolution de l'image : ";
    m_fr["OPT_TECHN_ANGLE"] = "angle_intervale : ";
    
    m_fr["OPT_AVANCED_PARAMS"] = "Paramètres avancés";
    m_fr["OPT_VITESSE_SIMULATION"] = "Vitesse simulée";
    m_fr["OPT_VITESSE_CAPTEUR_ROUE"] = "Capteur roue";
    m_fr["OPT_VITESSE_PRISE_ISO"] = "Prise iso";
    m_fr["OPT_VITESSE_GPS"] = "GPS";
    m_fr["OPT_VITESSE_ROUE_D_CM"] = "diamètre de la roue - cm";
    m_fr["OPT_VITESSE_SIMULATION_KM_H"] = "vitesse simulée - km/h";
    m_fr["OPT_VITESSE_DISCLAIMER"] = "Attention : ce mode n'est disponible que\n pour des opérations de maintenance \net sous la responsabilité de l'opérateur";
    m_fr["OPT_AMPLITUDE_CM"] = "amplitude max - cm";
    m_fr["OPT_CAMERA_AUTO_TITLE"] = "Changement automatique des caméras";
    
    m_fr["OPT_LUM"] = "Luminosité";
    m_fr["OPT_LANGUAGE"] = "Langue";
    m_fr["OPT_SON"] = "Son";
    m_fr["OPT_SON_3POINT"] = "alerte recentrage 3ème point";
    m_fr["OPT_SON_IMAGE"] = "alerte qualité image";
    m_fr["OPT_SON_VITESSE"] = "alerte vitesse";

    m_fr["OPT_PARAM_TRANSLATEUR"] = "Paramétrage du translateur";
    m_fr["OPT_HYDRAULIQUE"] = "Hydraulique";
    m_fr["OPT_TEST_TRANSLATEUR"] = "Tester le mouvement du translateur";
    m_fr["OPT_TEST_TRANSLATEUR2"] = "Tester le déplacement du translateur";

    m_fr["OPT_CENTER"] = "Recentrage de la bineuse";
    m_fr["OPT_CENTER2"] = "retour à zéro";
    m_fr["OPT_CONTRAINT"] = "Contraindre le translateur";
    m_fr["OPT_CONTRAINT2"] = "Limiter le mouvement du translateur";

    m_fr["OPT_PARAM"] = "Paramétrage du translateur";
    m_fr["OPT_IMAGE"] = "Traitement d'image";

    m_fr["OPT_TRANSLATEUR"] = "translateur";
    m_fr["OPT_NONE"] = "aucun";
    
    m_fr["OPT_JOYSTICK"] = "joystick";
    
    m_fr["HYDR_V_MAX"] = "vitesse max (cm/s) : ";
    m_fr["HYDR_AGRESS"] = "agressivité hydraulique : ";
    
    m_fr["HYDR_INV_RELAI"] = "inverse relai";
    m_fr["HYDR_DEBATTEMENT"] = "débattement : ";
    m_fr["HYDR_TEMP_MIN"] = "temps min : ";
    m_fr["HYDR_TEMP_MAX"] = "temps max : ";

    m_fr["PLANT_REGLAGE_TITLE"] = "Changer de réglage";
    m_fr["SAVE"] = "Enregistrer";
    m_fr["LOAD"] = "Ouvrir";
    m_fr["DELETE"] = "Supprimer";
    
    m_fr["PLANT_LOAD_TITLE"] = "Ouvrir un réglage précédent";
    m_fr["PLANT_LOAD_LOAD"] = "Voulez vous ouvrir le réglage suivant :";
    
    m_fr["FR"] = "Français";
    m_fr["EN"] = "Anglais";
    m_fr["DE"] = "Allemand";
    
    m_fr["ERROR"] = "erreur";
    
    m_fr["YES"] = "Oui";
    m_fr["NO"] = "Non";


    //ENGLISH

    m_en["HOME_L1"] = "WARNING";
    m_en["HOME_L2"] = "- Activating the guidance system may cause unexpected movements.";
    m_en["HOME_L3"] = "- Switch off the steering and hydraulics when working on the machine.";
    m_en["HOME_L4"] = "- All material and human damage is the responsibility of the operator.";
    m_en["HOME_VERSION"] = "version ";
    m_en["ACCEPT"] = "Accept";
    
    m_en["MAIN_3POINT"] = "3 point hitch";
    m_en["MAIN_NOT_ENGAGED"] = "not activated";
    m_en["MAIN_POOR_QUALITY"] = "bad quality";
    m_en["MAIN_NOT_CONNECTED"] = "not connect";
    m_en["MAIN_UNKNOWN_ERROR"] = "unexpected error";
    m_en["MAIN_SCORE_LOW"] = "score too low";
    m_en["MAIN_TEMP"] = "not calibrated";

    m_en["MAIN_CALC"] = "cal : ";
    m_en["MAIN_SCORE"] = "score : ";
    m_en["MAIN_DEPL"] = "travel : ";
    m_en["MAIN_ANG"] = "angle : ";
    m_en["MAIN_VITESSE"] = "speed : ";
    
    m_en["PARAMS_TITLE"] = "Translator settings menu";
    m_en["PARAMS_P1_BEGIN"] = "You will start setting up the weeder's translator.";
    m_en["PARAMS_P1_SECURITY"] = "Make sure you can move the translator safely.";

    m_en["PARAMS_P2_TEST"] = "Test the left and right displacement.";
    m_en["PARAMS_P2_INVERSE_QUESTION"] = "Should they be reversed?";
    m_en["INVERSE"] = "Reverse relay";

    m_en["PARAMS_P3_MAX_LEFT"] = "Move the translator as far to the left as possible.";
    m_en["PARAMS_P4_MAX_RIGHT"] = "Move the translator as far to the right as possible.";
    m_en["PARAMS_P5_CENTER"] = "Recenter the translator.";

    m_en["PARAMS_P6_MESURE"] = "Measure the translator travel.";
    m_en["PARAMS_P6_DEBATTEMENT_CM"] = "Clearance ( cm )" ;
    m_en["PARAMS_P7_AGRESSIVITY"] = "Regulate aggressiveness.";;
    m_en["PARAMS_P7_PUT_MAX"] = "Increase the aggressiveness to the maximum, without the weeder oscillating.";
    m_en["PARAMS_P7_AGRESS"] = "Aggressiveness p : ";
    m_en["PARAMS_P7_TEST"] = "You can test the displacement.";

    m_en["RAPIDE_COEFF"] = "Coeff : ";
    m_en["RAPIDE_CONSTRASTE"] = "Contrast : ";

    m_en["RAPIDE_CAMERA"] = "camera";
    m_en["RAPIDE_HAUTEUR"] = "height (cm)";
    m_en["RAPIDE_ANGLE"] = "angle (°)";
    m_en["RAPIDE_CULTURE"] = "Crop";
    m_en["RAPIDE_NB_RANGS"] = "nbr row";
    m_en["RAPIDE_INTERRANG"] = "inter row (cm)";
    m_en["RAPIDE_EPAISSEUR"] = "thickness (cm)";
    m_en["RAPIDE_SCORE_MIN"] = "score min";

    m_en["RAPIDE_OFFSET"] = "offset";
    m_en["RAPIDE_DISTANCE"] = "distance (cm)";
    m_en["RAPIDE_DEVERS"] = "Tilt";
    m_en["RAPIDE_DISTANCE_SOC"] = "distance tif (cm)";

    m_en["NEXT"] = "Next";
    m_en["OK"] = "Ok";
    m_en["CANCEL"] = "Cancel";
    m_en["END"] = "End";
    m_en["LEFT"] = "Left";
    m_en["RIGHT"] = "Right";
    m_en["MIDDLE"] = "Middle";
    
    m_en["PLANTS"] = "Plants";
    m_en["HYDRAULIQUE"] = "Hydraulic";
    m_en["OPTIONS"] = "Option";
    m_en["CLOSE"] = "Close";
    
    m_en["OPT_AV_TITLE"] = "Advanced";
    m_en["OPT_AV_TECHNICIEN"] = "Technician";
    m_en["OPT_AV_AVANCE"] = "Advanced";
    m_en["OPT_AV_DEBUG"] = "Debug";
    m_en["OPT_CONN_TITLE"] = "Connection";
    m_en["OPT_CONN_CART"] = "Control card ";
    m_en["OPT_CAMERA_NBR"] = "cameras : ";
    m_en["OPT_CAMERA_1"] = "camera 1 :";
    m_en["OPT_CAMERA_2"] = "camera 2 :";
    m_en["OPT_CAMERA_AUTO"] = "auto camera";
    m_en["OPT_TECHN_TITLE"] = "Technician option";
    m_en["OPT_TECHN_FOCAL"] = "focal : ";
    m_en["OPT_TECHN_MULTI_THREAD"] = "multi_thread";
    m_en["OPT_TECHN_RESOLUTION"] = "image resolution : ";
    m_en["OPT_TECHN_ANGLE"] = "interval angle : ";
    
    m_en["HYDR_V_MAX"] = "max speed of the translator (cm/s) : ";
    m_en["HYDR_AGRESS"] = "hydraulic aggressiveness : ";
    
    m_en["HYDR_INV_RELAI"] = "reverse relay";
    m_en["HYDR_DEBATTEMENT"] = "deflection : ";
    m_en["HYDR_TEMP_MIN"] = "temp min : ";
    m_en["HYDR_TEMP_MAX"] = "temp max : ";

    m_en["PLANT_REGLAGE_TITLE"] = "Change setting";
    m_en["SAVE"] = "Save";
    m_en["LOAD"] = "Open";
    m_en["DELETE"] = "Delete";
    
    m_en["PLANT_LOAD_TITLE"] = "Open a previous setting";
    m_en["PLANT_LOAD_LOAD"] = "Do you want to open the following setting :";
    
    m_en["YES"] = "Yes";
    m_en["NO"] = "No";



    //ALLEMAND
    m_de["HOME_L1"] = "WARNUNG";
    m_de["HOME_L2"] = "- Die Aktivierung des Lenksystems kann zu unerwarteten Bewegungen führen.";
    m_de["HOME_L3"] = "- Schalten Sie bei allen Arbeiten an der Maschine die Lenkung und die Hydraulik aus.";
    m_de["HOME_L4"] = "- Für alle Sach- und Personenschäden ist der Betreiber verantwortlich.";
    m_de["ACCEPT"] = "Annehmen";
    m_de["HOME_VERSION"] = "Ausführung ";

    m_de["MAIN_3POINT"] = "3-Punkt-Kupplung";
    m_de["MAIN_NOT_ENGAGED"] = "nicht aktiviert";
    m_de["MAIN_POOR_QUALITY"] = "geringe Qualität";
    m_de["MAIN_NOT_CONNECTED"] = "nicht angeschlossen";
    m_de["MAIN_UNKNOWN_ERROR"] = "unbekannter Fehler";
    m_de["MAIN_SCORE_LOW"] = "Punktzahl zu niedrig";
        
    m_de["MAIN_CALC"] = "berechnung : ";
    m_de["MAIN_SCORE"] = "ergebnis : ";
    m_de["MAIN_DEPL"] = "reisen : ";
    m_de["MAIN_ANG"] = "winkel : ";
    m_de["MAIN_VITESSE"] = "geschwindigkeit : ";

    m_de["PARAMS_TITLE"] = "Menü Übersetzer-Einstellungen";
    m_de["PARAMS_P1_BEGIN"] = "Sie sind dabei, den Übersetzer des Unkrautvernichters einzurichten.";
    m_de["PARAMS_P1_SECURITY"] = "Stellen Sie sicher, dass Sie den Übersetzer sicher bewegen können.";

    m_de["PARAMS_P2_TEST"] = "Testen Sie die Links-Rechts-Bewegung.";
    m_de["PARAMS_P2_INVERSE_QUESTION"] = "Sollten sie rückgängig gemacht werden?";
    m_de["INVERSE"] = "Umkehrrelais";

    m_de["PARAMS_P3_MAX_LEFT"] = "Bewegen Sie den Übersetzer so weit wie möglich nach links.";
    m_de["PARAMS_P4_MAX_RIGHT"] = "Bewegen Sie den Übersetzer so weit wie möglich nach rechts.";
    m_de["PARAMS_P5_CENTER"] = "Richten Sie den Übersetzer neu aus.";

    m_de["PARAMS_P6_MESURE"] = "Messen Sie die Gesamtverschiebung des Übersetzers.";
    m_de["PARAMS_P6_DEBATTEMENT_CM"] = "Freigabe ( cm ) " ;
    m_de["PARAMS_P7_AGRESSIVITY"] = "Aggressionen regulieren.";;
    m_de["PARAMS_P7_PUT_MAX"] = "Erhöhen Sie die Aggressivität bis zum Maximum, ohne dass der Unkrautstecher oszilliert.";
    m_de["PARAMS_P7_AGRESS"] = "Aggression p : ";
    m_de["PARAMS_P7_TEST"] = "Sie können die Verdrängung testen.";

    m_de["RAPIDE_COEFF"] = "coeff : ";
    m_de["RAPIDE_CONSTRASTE"] = "Kontrast : ";

    m_de["RAPIDE_CAMERA"] = "Kamera";
    m_de["RAPIDE_HAUTEUR"] = "Höhe (cm)";
    m_de["RAPIDE_ANGLE"] = "Winkel (°)";
    m_de["RAPIDE_CULTURE"] = "Kultur";
    m_de["RAPIDE_NB_RANGS"] = "Anzahl der Zeilen";
    m_de["RAPIDE_INTERRANG"] = "zwischen den Reihen (cm)";
    m_de["RAPIDE_EPAISSEUR"] = "Dicke (cm)";
    m_de["RAPIDE_SCORE_MIN"] = "Mindestpunktzahl";

    m_de["RAPIDE_OFFSET"] = "Versatz";
    m_de["RAPIDE_DISTANCE"] = "Entfernung (cm)";
    m_de["RAPIDE_DEVERS"] = "devers";
    m_de["RAPIDE_DISTANCE_SOC"] = "Entfernung Element (cm)";

    m_de["NEXT"] = "Weiter";
    m_de["OK"] = "Ok";
    m_de["CANCEL"] = "Abbrechen";
    m_de["END"] = "Ende";
    m_de["LEFT"] = "Links";
    m_de["RIGHT"] = "Rechts";
    m_de["MIDDLE"] = "Umwelt";
    
    m_de["PLANTS"] = "Pflanzen";
    m_de["HYDRAULIQUE"] = "Hydraulisch";
    m_de["OPTIONS"] = "Option";
    m_de["CLOSE"] = "Beenden";
    
    m_de["OPT_AV_TITLE"] = "Erweitert";
    m_de["OPT_AV_TECHNICIEN"] = "Techniker";
    m_de["OPT_AV_AVANCE"] = "Techniker";
    m_de["OPT_AV_DEBUG"] = "Debuggen";
    m_de["OPT_CONN_TITLE"] = "Verbindung";
    m_de["OPT_CONN_CART"] = "Steuerkarte ";
    m_de["OPT_CAMERA_NBR"] = "Kameras : ";
    m_de["OPT_CAMERA_1"] = "Kamera 1 :";
    m_de["OPT_CAMERA_2"] = "Kamera 2 :";
    m_de["OPT_CAMERA_AUTO"] = "automatische Kamera";
    m_de["OPT_TECHN_TITLE"] = "Techniker-Option";
    m_de["OPT_TECHN_FOCAL"] = "fokal : ";
    m_de["OPT_TECHN_MULTI_THREAD"] = "multi_thread";
    m_de["OPT_TECHN_RESOLUTION"] = "Bildauflösung : ";
    m_de["OPT_TECHN_ANGLE"] = "Winkelintervall : ";
    
    m_de["HYDR_V_MAX"] = "maximale Geschwindigkeit des Übersetzers (cm / s) : ";
    m_de["HYDR_AGRESS"] = "hydraulische Aggressivität : ";
    
    m_de["HYDR_INV_RELAI"] = "Rückwärtsrelais";
    m_de["HYDR_DEBATTEMENT"] = "Ablenkung : ";
    m_de["HYDR_TEMP_MIN"] = "Min. Zeit : ";
    m_de["HYDR_TEMP_MAX"] = "Max. Zeit : ";

    m_de["PLANT_REGLAGE_TITLE"] = "Einstellung ändern";
    m_de["SAVE"] = "Speichern";
    m_de["LOAD"] = "Öffnen";
    m_de["DELETE"] = "Löschen";
    
    m_de["PLANT_LOAD_TITLE"] = "Öffne eine vorherige Einstellung";
    m_de["PLANT_LOAD_LOAD"] = "Möchten Sie die folgende Einstellung öffnen :";
    
    m_de["YES"] = "Ja";
    m_de["NO"] = "Nein";
    
    /*std::unordered_map<std::string, int> m_all;
    for(auto pair : m_fr){
        std::string s = pair.first;
        if(m_all.find(s) == m_all.end()){
            m_all[s] = 1;
        }
    }
    
    for(auto pair : m_en){
        std::string s = pair.first;
        if(m_all.find(s) == m_all.end()){
            m_all[s] = 1;
        }
    }
    
    for(auto pair : m_de){
        std::string s = pair.first;
        if(m_all.find(s) == m_all.end()){
            m_all[s] = 1;
        }
    }
    
    
    std::ofstream myfile;
    myfile.open ("/Users/lemairec/workspace/bineuse/all.txt");
    for(auto pair : m_all){
        std::string s = pair.first;
        myfile << s << "\n";
        
    }
    myfile.close();*/
}
