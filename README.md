# wxBiApi

Binance API расширение C++.

### Необходимые библиотеки

1. [wxWidgets](https://www.wxwidgets.org/https:/)
2. [libcurl](https://curl.se/download.htmlhttps:/)
3. [boost](https://www.boost.org/https:/)
4. [OpenSSL](https://www.openssl.org/source/https:/)

### Формат возвращаемых значение

Json -> Bapi::Json

## Содание объекта

```
  WxBinanceApi *binApi = new WxBinanceApi();
```

### Подключение событий

```
binApi->fapi->Bind(BAPI_RET_DATA, &<Название текущего класса>::LoadData, this);
```

### Тип данных REST

* RestEventData::TypeRestEvent::NONE                // Нет типа
* RestEventData::TypeRestEvent::PING                // https://binance-docs.github.io/apidocs/futures/en/#test-connectivity
* RestEventData::TypeRestEvent::CheckServerTime     // https://binance-docs.github.io/apidocs/futures/en/#check-server-time
* RestEventData::TypeRestEvent::ExchangeInformation // https://binance-docs.github.io/apidocs/futures/en/#exchange-information

### Функция получения событий

```
void <Название текущего класса>::LoadData(RestEventData& event){
      std::cout << event.getData().dump() << std::endl; // Вывод Json данных
      std::cout << event.GetTypeREST() << std::endl; // Вывод Тип данных REST
}
```
