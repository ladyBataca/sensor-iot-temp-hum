idf_component_register(SRCS "sensor-iot-temp-hum.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES index.html)
list(APPEND EXTRA_COMPONENT_DIRS components)