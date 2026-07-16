/******************************************************************************************************************************/
/* ABLS-AGENT-SHELLY/shelly.c  Gestion des agents SHELLY                                                                     */
/* Projet Abls-Habitat                   Gestion d'habitat                                                08.03.2024 23:35:42 */
/* Auteur: LEFEVRE Sebastien                                                                                                  */
/******************************************************************************************************************************/
/*
 * Shelly.c
 * This file is part of Abls-Habitat
 *
 * Copyright (C) 1988-2026 - Sébastien LEFÈVRE
 *
 * ABLS-AGENT-SHELLY is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ABLS-AGENT-SHELLY is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ABLS-AGENT-SHELLY; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

 #include "shelly.h"

/******************************************************************************************************************************/
/* Run_thread: Prend en charge un des sous thread de l'agent                                                                  */
/* Entrée: la structure THREAD associée                                                                                       */
/* Sortie: Niet                                                                                                               */
/******************************************************************************************************************************/
 gint main ( gint argc, gchar *argv[] )
  { struct ABLS_AGENT *agent = Agent_init ( argv[0], "shelly", ABLS_AGENT_SHELLY_VERSION, sizeof(struct ABLS_SHELLY_VARS), argc, argv );
    struct ABLS_SHELLY_VARS *vars = agent->vars;

    gchar *string_id   = Json_get_string ( agent->api_config, "string_id" );
    if (!string_id)
     { Info( __func__, agent->agent_classe, agent->agent_tech_id, LOG_ERR, "ERROR: No string_id, stopping thread" ); goto end; }

    gboolean shelly_pro_em_50 = g_str_has_prefix ( string_id, SHELLY_PRO_EM_50 );
    gboolean shelly_pro_3_em  = g_str_has_prefix ( string_id, SHELLY_PRO_3_EM );

    if (shelly_pro_em_50)                                                                               /* Monophasé 2 canaux */
     { Info( __func__, agent->agent_classe, agent->agent_tech_id, LOG_NOTICE, "Using SHELLY_PRO_EM_50 (monophasé)" );
       vars->EM10_ACT_POWER  = Mnemo_create_AI ( agent, "EM10_ACT_POWER",  "EM10 Puissance active", "W",     AGENT_ARCHIVE_1_MIN );
       vars->EM10_APRT_POWER = Mnemo_create_AI ( agent, "EM10_APRT_POWER", "EM10 Puissance apparente", "VA", AGENT_ARCHIVE_1_MIN );
       vars->EM10_CURRENT    = Mnemo_create_AI ( agent, "EM10_CURRENT",    "EM10 Courant", "A",              AGENT_ARCHIVE_1_MIN );
       vars->EM10_FREQ       = Mnemo_create_AI ( agent, "EM10_FREQ",       "EM10 Fréquence", "HZ",           AGENT_ARCHIVE_1_MIN );
       vars->EM10_PF         = Mnemo_create_AI ( agent, "EM10_PF",         "EM10 Facteur de charge", "",     AGENT_ARCHIVE_1_MIN );
       vars->EM10_VOLTAGE    = Mnemo_create_AI ( agent, "EM10_VOLTAGE",    "EM10 Voltage", "V",              AGENT_ARCHIVE_1_MIN );
       vars->EM10_ENERGY     = Mnemo_create_AI ( agent, "EM10_ENERGY",     "EM10 Energie consommée", "Wh",   AGENT_ARCHIVE_1_MIN );
       vars->EM10_INJECTION  = Mnemo_create_AI ( agent, "EM10_INJECTION",  "EM10 Energie injectée", "Wh",    AGENT_ARCHIVE_1_MIN );
       vars->EM10_INDEX_IN   = Mnemo_create_AI ( agent, "EM10_INDEX_IN",   "EM10 Index de puissance consommée", "Wh", AGENT_ARCHIVE_1_MIN );
       vars->EM10_INDEX_OUT  = Mnemo_create_AI ( agent, "EM10_INDEX_OUT",  "EM10 Index de puissance injectée",  "Wh", AGENT_ARCHIVE_1_MIN );
       vars->EM10_RESET_INDEX_IN  = Mnemo_create_DO ( agent, "EM10_RESET_INDEX_IN",  "EM10 Réinitialiser l'index de puissance consommée", TRUE );
       vars->EM10_RESET_INDEX_OUT = Mnemo_create_DO ( agent, "EM10_RESET_INDEX_OUT", "EM10 Réinitialiser l'index de puissance injectée", TRUE );

       vars->EM11_ACT_POWER  = Mnemo_create_AI ( agent, "EM11_ACT_POWER",  "EM11 Puissance active", "W",     AGENT_ARCHIVE_1_MIN );
       vars->EM11_APRT_POWER = Mnemo_create_AI ( agent, "EM11_APRT_POWER", "EM11 Puissance apparente", "VA", AGENT_ARCHIVE_1_MIN );
       vars->EM11_CURRENT    = Mnemo_create_AI ( agent, "EM11_CURRENT",    "EM11 Courant", "A",              AGENT_ARCHIVE_1_MIN );
       vars->EM11_FREQ       = Mnemo_create_AI ( agent, "EM11_FREQ",       "EM11 Fréquence", "HZ",           AGENT_ARCHIVE_1_MIN );
       vars->EM11_PF         = Mnemo_create_AI ( agent, "EM11_PF",         "EM11 Facteur de charge", "",     AGENT_ARCHIVE_1_MIN );
       vars->EM11_VOLTAGE    = Mnemo_create_AI ( agent, "EM11_VOLTAGE",    "EM11 Voltage", "V",              AGENT_ARCHIVE_1_MIN );
       vars->EM11_ENERGY     = Mnemo_create_AI ( agent, "EM11_ENERGY",     "EM11 Energie consommée", "Wh",   AGENT_ARCHIVE_1_MIN );
       vars->EM11_INJECTION  = Mnemo_create_AI ( agent, "EM11_INJECTION",  "EM11 Energie injectée", "Wh",    AGENT_ARCHIVE_1_MIN );
       vars->EM11_INDEX_IN   = Mnemo_create_AI ( agent, "EM11_INDEX_IN",   "EM11 Index de puissance consommée", "Wh", AGENT_ARCHIVE_1_MIN );
       vars->EM11_INDEX_OUT  = Mnemo_create_AI ( agent, "EM11_INDEX_OUT",  "EM11 Index de puissance injectée",  "Wh", AGENT_ARCHIVE_1_MIN );
       vars->EM11_RESET_INDEX_IN  = Mnemo_create_DO ( agent, "EM11_RESET_INDEX_IN",  "EM11 Réinitialiser l'index de puissance consommée", TRUE );
       vars->EM11_RESET_INDEX_OUT = Mnemo_create_DO ( agent, "EM11_RESET_INDEX_OUT", "EM11 Réinitialiser l'index de puissance injectée", TRUE );
     }
    else if (shelly_pro_3_em)                                                                                     /* Triphasé */
     { Info( __func__, agent->agent_classe, agent->agent_tech_id, LOG_NOTICE, "Using SHELLY_PRO_3_EM (triphasé)" );
       vars->U1          = Mnemo_create_AI ( agent, "U1",           "Voltage Phase 1", "V", AGENT_ARCHIVE_1_MIN );
       vars->U2          = Mnemo_create_AI ( agent, "U2",           "Voltage Phase 2", "V", AGENT_ARCHIVE_1_MIN );
       vars->U3          = Mnemo_create_AI ( agent, "U3",           "Voltage Phase 3", "V", AGENT_ARCHIVE_1_MIN );
       vars->I1          = Mnemo_create_AI ( agent, "I1",           "Courant Phase 1", "A", AGENT_ARCHIVE_1_MIN );
       vars->I2          = Mnemo_create_AI ( agent, "I2",           "Courant Phase 2", "A", AGENT_ARCHIVE_1_MIN );
       vars->I3          = Mnemo_create_AI ( agent, "I3",           "Courant Phase 3", "A", AGENT_ARCHIVE_1_MIN );
       vars->I_TOTAL     = Mnemo_create_AI ( agent, "I_TOTAL",      "Courant Total", "A", AGENT_ARCHIVE_1_MIN );
       vars->ACT_TOTAL   = Mnemo_create_AI ( agent, "ACT_TOTAL",    "Puissance Active Totale", "W", AGENT_ARCHIVE_1_MIN );
       vars->ACT_POWER1  = Mnemo_create_AI ( agent, "ACT_POWER1",   "Puissance Active Phase 1", "W", AGENT_ARCHIVE_1_MIN );
       vars->ACT_POWER2  = Mnemo_create_AI ( agent, "ACT_POWER2",   "Puissance Active Phase 2", "W", AGENT_ARCHIVE_1_MIN );
       vars->ACT_POWER3  = Mnemo_create_AI ( agent, "ACT_POWER3",   "Puissance Active Phase 3", "W", AGENT_ARCHIVE_1_MIN );
       vars->APRT_TOTAL  = Mnemo_create_AI ( agent, "APRT_TOTAL",   "Puissance Apparente Totale", "VA", AGENT_ARCHIVE_1_MIN );
       vars->APRT_POWER1 = Mnemo_create_AI ( agent, "APRT_POWER1",  "Puissance Apparente Phase 1", "VA", AGENT_ARCHIVE_1_MIN );
       vars->APRT_POWER2 = Mnemo_create_AI ( agent, "APRT_POWER2",  "Puissance Apparente Phase 2", "VA", AGENT_ARCHIVE_1_MIN );
       vars->APRT_POWER3 = Mnemo_create_AI ( agent, "APRT_POWER3",  "Puissance Apparente Phase 3", "VA", AGENT_ARCHIVE_1_MIN );
       vars->FREQ1       = Mnemo_create_AI ( agent, "FREQ1",        "Fréquence Phase 1", "HZ", AGENT_ARCHIVE_1_MIN );
       vars->FREQ2       = Mnemo_create_AI ( agent, "FREQ2",        "Fréquence Phase 2", "HZ", AGENT_ARCHIVE_1_MIN );
       vars->FREQ3       = Mnemo_create_AI ( agent, "FREQ3",        "Fréquence Phase 3", "HZ", AGENT_ARCHIVE_1_MIN );
       vars->PF1         = Mnemo_create_AI ( agent, "PF1",          "Facteur de charge Phase 1", "cos", AGENT_ARCHIVE_1_MIN );
       vars->PF2         = Mnemo_create_AI ( agent, "PF2",          "Facteur de charge Phase 2", "cos", AGENT_ARCHIVE_1_MIN );
       vars->PF3         = Mnemo_create_AI ( agent, "PF3",          "Facteur de charge Phase 3", "cos", AGENT_ARCHIVE_1_MIN );
       vars->ENERGY1     = Mnemo_create_AI ( agent, "ENERGY1",      "Energie consommée Phase 1", "Wh",   AGENT_ARCHIVE_1_MIN );
       vars->ENERGY2     = Mnemo_create_AI ( agent, "ENERGY2",      "Energie consommée Phase 2", "Wh",   AGENT_ARCHIVE_1_MIN );
       vars->ENERGY3     = Mnemo_create_AI ( agent, "ENERGY3",      "Energie consommée Phase 3", "Wh",   AGENT_ARCHIVE_1_MIN );
       vars->INJECTION1  = Mnemo_create_AI ( agent, "INJECTION1",   "Energie injectée Phase 1", "Wh",    AGENT_ARCHIVE_1_MIN );
       vars->INJECTION2  = Mnemo_create_AI ( agent, "INJECTION2",   "Energie injectée Phase 2", "Wh",    AGENT_ARCHIVE_1_MIN );
       vars->INJECTION3  = Mnemo_create_AI ( agent, "INJECTION3",   "Energie injectée Phase 3", "Wh",    AGENT_ARCHIVE_1_MIN );
       vars->INDEX_IN1   = Mnemo_create_AI ( agent, "INDEX_IN1",   "EM11 Index de puissance consommée Phase 1", "Wh", AGENT_ARCHIVE_1_MIN );
       vars->INDEX_IN2   = Mnemo_create_AI ( agent, "INDEX_IN2",   "EM11 Index de puissance consommée Phase 2", "Wh", AGENT_ARCHIVE_1_MIN );
       vars->INDEX_IN3   = Mnemo_create_AI ( agent, "INDEX_IN3",   "EM11 Index de puissance consommée Phase 3", "Wh", AGENT_ARCHIVE_1_MIN );
       vars->INDEX_OUT1  = Mnemo_create_AI ( agent, "INDEX_OUT1",  "EM11 Index de puissance injectée Phase 1",  "Wh", AGENT_ARCHIVE_1_MIN );
       vars->INDEX_OUT2  = Mnemo_create_AI ( agent, "INDEX_OUT2",  "EM11 Index de puissance injectée Phase 2",  "Wh", AGENT_ARCHIVE_1_MIN );
       vars->INDEX_OUT3  = Mnemo_create_AI ( agent, "INDEX_OUT3",  "EM11 Index de puissance injectée Phase 3",  "Wh", AGENT_ARCHIVE_1_MIN );
       vars->RESET_INDEX_IN1  = Mnemo_create_DO ( agent, "RESET_INDEX_IN1",  "Réinitialiser l'index de puissance consommée Phase 1", TRUE );
       vars->RESET_INDEX_IN2  = Mnemo_create_DO ( agent, "RESET_INDEX_IN2",  "Réinitialiser l'index de puissance consommée Phase 2", TRUE );
       vars->RESET_INDEX_IN3  = Mnemo_create_DO ( agent, "RESET_INDEX_IN3",  "Réinitialiser l'index de puissance consommée Phase 3", TRUE );
       vars->RESET_INDEX_OUT1 = Mnemo_create_DO ( agent, "RESET_INDEX_OUT1", "Réinitialiser l'index de puissance injectée Phase 1", TRUE );
       vars->RESET_INDEX_OUT2 = Mnemo_create_DO ( agent, "RESET_INDEX_OUT2", "Réinitialiser l'index de puissance injectée Phase 2", TRUE );
       vars->RESET_INDEX_OUT3 = Mnemo_create_DO ( agent, "RESET_INDEX_OUT3", "Réinitialiser l'index de puissance injectée Phase 3", TRUE );
     }
    else
      { Info( __func__, agent->agent_classe, agent->agent_tech_id, LOG_ERR, "Shelly type '%s' not recognized", string_id ); goto end; }

    Mqtt_subscribe ( agent->mqtt_local, "%s/online", string_id );
    Mqtt_subscribe ( agent->mqtt_local, "%s/events/rpc", string_id );
    Mqtt_subscribe ( agent->mqtt_local, "%s/status/em1data:0", string_id );
    Mqtt_subscribe ( agent->mqtt_local, "%s/status/em1data:1", string_id );
    Mqtt_subscribe ( agent->mqtt_local, "%s/status/em1:0", string_id );
    Mqtt_subscribe ( agent->mqtt_local, "%s/status/em1:1", string_id );
    Mqtt_subscribe ( agent->mqtt_local, "%s/status/emdata:0", string_id );
    Mqtt_subscribe ( agent->mqtt_local, "%s/status/em:0", string_id );

    while(agent->Agent_run == AGENT_IS_RUNNING)                                              /* On tourne tant que necessaire */
     { Agent_loop ( agent );                                             /* Loop sur l'agent pour mettre a jour la telemetrie */
/****************************************************** Ecoute du master ******************************************************/
       JsonNode *mqtt_local_message;
       while ( (mqtt_local_message = Mqtt_get_message ( agent->mqtt_local ) ) != NULL )
        { if (Mqtt_topic_is ( mqtt_local_message, 2, "+", "online" ) )
           { gchar *payload = Json_get_string ( mqtt_local_message, "payload" );
             gboolean online = (payload && !strcasecmp ( payload, "true" ) ? TRUE : FALSE);
             Info( __func__, agent->agent_classe, agent->agent_tech_id, LOG_NOTICE, "Shelly '%s' is %s", string_id, (online ? "ONLINE" : "OFFLINE") );
             Agent_send_comm_to_master ( agent, online );
           }
          else if (Mqtt_topic_is ( mqtt_local_message, 3, "+", "events", "rpc" ) && Json_has_member ( mqtt_local_message, "method" ))
           { gchar *method = Json_get_string ( mqtt_local_message, "method" );
/*---------------------------------------------------- /event/rpc/ Notify Status ---------------------------------------------*/
             if (!strcmp ( method, "NotifyStatus" ) && Json_has_member ( mqtt_local_message, "params" ) )
              { JsonNode *params = Json_get_object_as_node ( mqtt_local_message, "params" );

                if (shelly_pro_em_50)                                                                  /* Monophasé, 2 canaux */
                 { if (Json_has_member ( params, "em1:0" ) )
                    { JsonNode *em = Json_get_object_as_node ( params, "em1:0" );
                      Mqtt_Send_AI ( agent, vars->EM10_ACT_POWER,  Json_get_double ( em, "act_power" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM10_APRT_POWER, Json_get_double ( em, "aprt_power" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM10_CURRENT,    Json_get_double ( em, "current" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM10_FREQ,       Json_get_double ( em, "freq" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM10_PF,         Json_get_double ( em, "pf" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM10_VOLTAGE,    Json_get_double ( em, "voltage" ), TRUE );
                    }
                   else if (Json_has_member ( params, "em1:1" ) )
                    { JsonNode *em = Json_get_object_as_node ( params, "em1:1" );
                      Mqtt_Send_AI ( agent, vars->EM11_ACT_POWER,  Json_get_double ( em, "act_power" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM11_APRT_POWER, Json_get_double ( em, "aprt_power" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM11_CURRENT,    Json_get_double ( em, "current" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM11_FREQ,       Json_get_double ( em, "freq" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM11_PF,         Json_get_double ( em, "pf" ), TRUE );
                      Mqtt_Send_AI ( agent, vars->EM11_VOLTAGE,    Json_get_double ( em, "voltage" ), TRUE );
                    }
                 }
                else if (shelly_pro_3_em && Json_has_member ( params, "em:0" ) )
                 { JsonNode *em = Json_get_object_as_node ( params, "em:0" );
                   Mqtt_Send_AI ( agent, vars->EM11_ACT_POWER, Json_get_double ( em, "act_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->U1            , Json_get_double ( em, "a_voltage" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->U2            , Json_get_double ( em, "b_voltage" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->U3            , Json_get_double ( em, "c_voltage" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->I1            , Json_get_double ( em, "a_current" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->I2            , Json_get_double ( em, "b_current" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->I3            , Json_get_double ( em, "c_current" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->I_TOTAL       , Json_get_double ( em, "total_current" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->ACT_TOTAL     , Json_get_double ( em, "total_act_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->ACT_POWER1    , Json_get_double ( em, "a_act_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->ACT_POWER2    , Json_get_double ( em, "b_act_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->ACT_POWER3    , Json_get_double ( em, "c_act_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->APRT_TOTAL    , Json_get_double ( em, "total_aprt_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->APRT_POWER1   , Json_get_double ( em, "a_aprt_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->APRT_POWER2   , Json_get_double ( em, "b_aprt_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->APRT_POWER3   , Json_get_double ( em, "c_aprt_power" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->FREQ1         , Json_get_double ( em, "a_freq" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->FREQ2         , Json_get_double ( em, "b_freq" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->FREQ3         , Json_get_double ( em, "c_freq" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->PF1           , Json_get_double ( em, "a_pf" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->PF2           , Json_get_double ( em, "b_pf" ), TRUE );
                   Mqtt_Send_AI ( agent, vars->PF3           , Json_get_double ( em, "c_pf" ), TRUE );
                 }
              }
/*---------------------------------------------------- /event/rpc Notify Event  ----------------------------------------------*/
             else if (!strcmp ( method, "NotifyEvent" ))
              { if (g_str_has_prefix ( string_id, SHELLY_PRO_EM_50 ) )
                 { JsonNode *params      = Json_get_object_as_node ( mqtt_local_message, "params" );
                   JsonArray *events     = Json_get_array ( params, "events" );
                   JsonNode *first_event = json_array_get_element ( events, 0 );
                   gchar *component      = Json_get_string ( first_event, "component" );
                   JsonNode *data        = Json_get_object_as_node ( first_event, "data" );
                   JsonArray *values     = Json_get_array ( data, "values" );
                              values     = json_array_get_array_element ( values, 0 ); /* Array in array */
                   gdouble energie       = json_array_get_double_element ( values, 0 );
                   gdouble injection     = json_array_get_double_element ( values, 1 );
                   if ( component )
                    { if (!strcmp ( component, "em1data:0" ) )
                       { Mqtt_Send_AI ( agent, vars->EM10_ENERGY, energie, TRUE );
                         Mqtt_Send_AI ( agent, vars->EM10_INJECTION, injection, TRUE );
                       }
                      else if (!strcmp ( component, "em1data:1" ) )
                       { Mqtt_Send_AI ( agent, vars->EM11_ENERGY, energie, TRUE );
                         Mqtt_Send_AI ( agent, vars->EM11_INJECTION, injection, TRUE );
                       }
                    }
                 }
                else if (g_str_has_prefix ( string_id, SHELLY_PRO_3_EM ) )
                 { JsonNode *params      = Json_get_object_as_node ( mqtt_local_message, "params" );
                   JsonArray *events     = Json_get_array ( params, "events" );
                   JsonNode *first_event = json_array_get_element ( events, 0 );
                   gchar *component      = Json_get_string ( first_event, "component" );
                   JsonNode *data        = Json_get_object_as_node ( first_event, "data" );
                   JsonArray *values     = Json_get_array ( data, "values" );
                              values     = json_array_get_array_element ( values, 0 ); /* Array in array */
                   gdouble energie1      = json_array_get_double_element ( values, 0 );
                   gdouble energie2      = json_array_get_double_element ( values, 16 );
                   gdouble energie3      = json_array_get_double_element ( values, 32 );
                   gdouble injection1    = json_array_get_double_element ( values, 2 );
                   gdouble injection2    = json_array_get_double_element ( values, 18 );
                   gdouble injection3    = json_array_get_double_element ( values, 34 );
                   if ( component && !strcmp ( component, "emdata:0" ) )
                    { Mqtt_Send_AI ( agent, vars->ENERGY1, energie1, TRUE );
                      Mqtt_Send_AI ( agent, vars->ENERGY2, energie2, TRUE );
                      Mqtt_Send_AI ( agent, vars->ENERGY3, energie3, TRUE );
                      Mqtt_Send_AI ( agent, vars->INJECTION1, injection1, TRUE );
                      Mqtt_Send_AI ( agent, vars->INJECTION2, injection2, TRUE );
                      Mqtt_Send_AI ( agent, vars->INJECTION3, injection3, TRUE );
                    }
                 }
              }
           }
/*---------------------------------------------------- /status ---------------------------------------------------------------*/
          else if (Mqtt_topic_is ( mqtt_local_message, 3, "+", "status", "em1:0" ) )                      /* Shelly monophasé */
           { Mqtt_Send_AI ( agent, vars->EM10_ACT_POWER,  Json_get_double ( mqtt_local_message, "act_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM10_APRT_POWER, Json_get_double ( mqtt_local_message, "aprt_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM10_CURRENT,    Json_get_double ( mqtt_local_message, "current" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM10_FREQ,       Json_get_double ( mqtt_local_message, "freq" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM10_PF,         Json_get_double ( mqtt_local_message, "pf" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM10_VOLTAGE,    Json_get_double ( mqtt_local_message, "voltage" ), TRUE );
           }
          else if (Mqtt_topic_is ( mqtt_local_message, 3, "+", "status", "em1:1" ) )
           { Mqtt_Send_AI ( agent, vars->EM11_ACT_POWER,  Json_get_double ( mqtt_local_message, "act_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM11_APRT_POWER, Json_get_double ( mqtt_local_message, "aprt_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM11_CURRENT,    Json_get_double ( mqtt_local_message, "current" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM11_FREQ,       Json_get_double ( mqtt_local_message, "freq" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM11_PF,         Json_get_double ( mqtt_local_message, "pf" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM11_VOLTAGE,    Json_get_double ( mqtt_local_message, "voltage" ), TRUE );
           }
          else if (Mqtt_topic_is ( mqtt_local_message, 3, "+", "status", "em1data:0" ) )
           { Mqtt_Send_AI ( agent, vars->EM10_INDEX_IN,  Json_get_double ( mqtt_local_message, "total_act_energy" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM10_INDEX_OUT, Json_get_double ( mqtt_local_message, "total_act_ret_energy" ), TRUE );
           }
          else if (Mqtt_topic_is ( mqtt_local_message, 3, "+", "status", "em1data:1" ) )
           { Mqtt_Send_AI ( agent, vars->EM11_INDEX_IN,  Json_get_double ( mqtt_local_message, "total_act_energy" ), TRUE );
             Mqtt_Send_AI ( agent, vars->EM11_INDEX_OUT, Json_get_double ( mqtt_local_message, "total_act_ret_energy" ), TRUE );
           }
          else if (Mqtt_topic_is ( mqtt_local_message, 3, "+", "status", "emdata:0" ) )              /* Shelly 3 EM, triphasé */
           { Mqtt_Send_AI ( agent, vars->INDEX_IN1,  Json_get_double ( mqtt_local_message, "a_total_act_energy" ), TRUE );
             Mqtt_Send_AI ( agent, vars->INDEX_IN2,  Json_get_double ( mqtt_local_message, "b_total_act_energy" ), TRUE );
             Mqtt_Send_AI ( agent, vars->INDEX_IN3,  Json_get_double ( mqtt_local_message, "c_total_act_energy" ), TRUE );
             Mqtt_Send_AI ( agent, vars->INDEX_OUT1, Json_get_double ( mqtt_local_message, "a_total_act_ret_energy" ), TRUE );
             Mqtt_Send_AI ( agent, vars->INDEX_OUT2, Json_get_double ( mqtt_local_message, "b_total_act_ret_energy" ), TRUE );
             Mqtt_Send_AI ( agent, vars->INDEX_OUT3, Json_get_double ( mqtt_local_message, "c_total_act_ret_energy" ), TRUE );
           }
          else if (Mqtt_topic_is ( mqtt_local_message, 3, "+", "status", "em:0" ) )                  /* Shelly 3 EM, triphasé */
           { Mqtt_Send_AI ( agent, vars->EM11_ACT_POWER, Json_get_double ( mqtt_local_message, "act_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->U1            , Json_get_double ( mqtt_local_message, "a_voltage" ), TRUE );
             Mqtt_Send_AI ( agent, vars->U2            , Json_get_double ( mqtt_local_message, "b_voltage" ), TRUE );
             Mqtt_Send_AI ( agent, vars->U3            , Json_get_double ( mqtt_local_message, "c_voltage" ), TRUE );
             Mqtt_Send_AI ( agent, vars->I1            , Json_get_double ( mqtt_local_message, "a_current" ), TRUE );
             Mqtt_Send_AI ( agent, vars->I2            , Json_get_double ( mqtt_local_message, "b_current" ), TRUE );
             Mqtt_Send_AI ( agent, vars->I3            , Json_get_double ( mqtt_local_message, "c_current" ), TRUE );
             Mqtt_Send_AI ( agent, vars->I_TOTAL       , Json_get_double ( mqtt_local_message, "total_current" ), TRUE );
             Mqtt_Send_AI ( agent, vars->ACT_TOTAL     , Json_get_double ( mqtt_local_message, "total_act_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->ACT_POWER1    , Json_get_double ( mqtt_local_message, "a_act_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->ACT_POWER2    , Json_get_double ( mqtt_local_message, "b_act_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->ACT_POWER3    , Json_get_double ( mqtt_local_message, "c_act_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->APRT_TOTAL    , Json_get_double ( mqtt_local_message, "total_aprt_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->APRT_POWER1   , Json_get_double ( mqtt_local_message, "a_aprt_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->APRT_POWER2   , Json_get_double ( mqtt_local_message, "b_aprt_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->APRT_POWER3   , Json_get_double ( mqtt_local_message, "c_aprt_power" ), TRUE );
             Mqtt_Send_AI ( agent, vars->FREQ1         , Json_get_double ( mqtt_local_message, "a_freq" ), TRUE );
             Mqtt_Send_AI ( agent, vars->FREQ2         , Json_get_double ( mqtt_local_message, "b_freq" ), TRUE );
             Mqtt_Send_AI ( agent, vars->FREQ3         , Json_get_double ( mqtt_local_message, "c_freq" ), TRUE );
             Mqtt_Send_AI ( agent, vars->PF1           , Json_get_double ( mqtt_local_message, "a_pf" ), TRUE );
             Mqtt_Send_AI ( agent, vars->PF2           , Json_get_double ( mqtt_local_message, "b_pf" ), TRUE );
             Mqtt_Send_AI ( agent, vars->PF3           , Json_get_double ( mqtt_local_message, "c_pf" ), TRUE );
           }
          Json_unref ( mqtt_local_message );
        }
     }
end:
    Agent_end(agent);
  }
/*----------------------------------------------------------------------------------------------------------------------------*/
