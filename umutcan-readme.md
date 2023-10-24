Kodu çalıştırma

    CSV2JSON <CSV dosya adı> <json dosya adı> <header=ON | OFF>
    varsayılan olarak headerların kapalı olduğu durum ele alınmıştır.

Açıklama
    Kodun başlangıcında giriş ve çıkış dosyaları argv şeklinde eşitlenir.
    check_headers fonksiyonu sayesinde 3. argüman okunarak headerlı mı headersız mı işlem yapılacağına karar verilir.
    headerlı işlem yapılacağında her header için bellekten yer ayrılır ve headerlar dosyanın ilk satırından okunarak kaydedilir.
    daha sonra değerler okundukça bir yandan çıkış dosyasına print_json_header ve print_json fonksiyonlarıyla yazılır.
    bu iki fonksiyonun arasındaki fark ise header varken print_json_header
    yokken prnt_json fonksiyonu kullanılır.