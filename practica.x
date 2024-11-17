struct Posicion{
  int x;
  int y;
};

struct InfoAuto {
  Posicion posicion_auto;
  string tipo<10>;
  float tarifa;
  string placa<7>;
};

struct InfoServicio {
  int viajes_realizados;
  int autos_libres;
  float ganancia;
};

program DISPLAY_PRG {
  version DISPLAY_VER {
    InfoAuto solicitarViaje(Posicion) =  1;
    void terminarViaje(Posicion, float, string) = 2;
    InfoServicio estadoServicio() = 3;
  } = 1;
} = 0x20000199;