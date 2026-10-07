

#include <iostream>
#include <string>
using namespace std;

// объявили до класса
enum TransportType {
	bus, trolleybus, tram, minibus
};

class Vehicle {
private:
	string vehicleNumber;
	TransportType type;
	double fuelPer100km;
	double mileageKm;
	bool isAvailable;
	void validate() {
		// приватный метод валидации — вызывается из конструктора и сеттеров
		if (vehicleNumber.length() != 8) {
			cout << "Предупреждение: номер должен быть 8 символов. Установлено 'XXXXXXX-0'." << endl;
			vehicleNumber = "XXXXXXX-0";
		}
		if (fuelPer100km < 0.0 || fuelPer100km > 100.0) {
			cout << "Предупреждение: расход вне диапазона [0..100]. Установлено 0." << endl;
			fuelPer100km = 0.0;
		}
		if (mileageKm < 0.0 || mileageKm > 1000000.0) {
			cout << "Предупреждение: пробег вне диапазона [0..1 000 000]. Установлено 0." << endl;
			mileageKm = 0.0;
		}
	}

public:
	// конструктор по умолчанию
	Vehicle() : vehicleNumber(""), type(bus), fuelPer100km(0.0), mileageKm(0.0),
		isAvailable(true)
	{
		// тут можно писать валидацию, но здесь она не нужна: задан шаблон мной
	}

	Vehicle(string number, TransportType transport, double fuel, double mileage, bool available)
		: vehicleNumber(number), type(transport), fuelPer100km(fuel), mileageKm(mileage), isAvailable(available)
	{
		// валидация после списка инициализации
		validate();
	}

	~Vehicle() {
		cout << "Объект " << vehicleNumber << " уничтожен" << endl;
	}

	// геттеры
	string getVehicleNumber() const {
		return vehicleNumber;
	}
	TransportType getType() const {
		return type;
	}
	double getFuelPer100km() const {
		return fuelPer100km;
	}
	double getMileageKm() const {
		return mileageKm;
	}
	bool getIsAvailable() const {
		return isAvailable;
	}

	// Возвращает тип транспорта как строку
	string getTypeAsString() const {
		switch (type) {
		case bus:        return "Автобус";
		case trolleybus: return "Троллейбус";
		case tram:       return "Трамвай";
		case minibus:    return "Маршрутка";
		default:         return "Неизвестно";
		}
	}


	// сеттеры
	void setVehicleNumber(string number) {

		vehicleNumber = number;
		validate();
	}
	void setType(TransportType transport) {
		type = transport;
	}
	void setFuelPer100km(double fuel) {
		fuelPer100km = fuel;
		validate();
	}
	void setMileageKm(double mileage) {
		mileageKm = mileage;
		validate();
	}

	void setIsAvailable(bool available) {
		isAvailable = available;
	}


	// методы

	// методы расчета
	double fuelConsumptionCalculation() const {
		return (mileageKm / 100.0) * fuelPer100km;
	}

	// новый метод - расчет стоимости топлива при заданной цене за литр
	double calculateFuelCost(double pricePerLiter) const {
		if (pricePerLiter < 0.0) {
			cout << "Ошибка: цена не может быть отрицательной!" << endl;
			return 0.0;
		}
		return fuelConsumptionCalculation() * pricePerLiter;
	}

	// методы изменения

	// новый метод - добавить пробег
	void updateMileage(double km) {
		if (km > 0.0 && (mileageKm + km) <= 1000000.0) {
			mileageKm += km;
			cout << "Пробег увеличен на " << km << " км. Текущий пробег: "
				<< mileageKm << " км." << endl;
		}
		else {
			cout << "Ошибка: пробег не может быть отрицательным или превышать 1 000 000 км!" << endl;
		}
	}

	void changeAvailableStatus() {
		isAvailable = !isAvailable;
		cout << "Статус изменен. Теперь: " << (isAvailable ? "Доступен" : "Недоступен") << endl;
	}

	void printInfo() const {
		cout << "=================================================" << endl;
		cout << "Номер транспортного средства: " << vehicleNumber << endl;
		cout << "Тип транспорта: " << getTypeAsString() << endl;
		cout << "Расход топлива на 100 км: " << fuelPer100km << endl;
		cout << "Пробег (км): " << mileageKm << endl;
		cout << "Статус доступности: " << (isAvailable ? "Доступен" : "Недоступен") << endl;
		cout << "=================================================" << endl;
	}
};

int main() {
	// создание массива
	Vehicle vehicleFleet[6] = {
	Vehicle("E2363B-7", bus, 20.5, 20020.41, true),
	Vehicle("E7777A-7", tram, 33.3, 25730.29, false),
	Vehicle("E5433C-7", minibus, 27.5, 52000.78, true),
	Vehicle("E5763G-7", trolleybus, 25.9, 12000.15, false),
	Vehicle("E2533B-7", minibus, 21.4, 20760.63, true),
	Vehicle("E1111A-7", bus, 23.5, 200.43, true)
	};

	for (int i = 0; i < 6; i++) {
		cout << "Транспорт " << vehicleFleet[i].getVehicleNumber() << " израсходовал " << vehicleFleet[i].fuelConsumptionCalculation() << " л" << endl;
	}

	cout << "Изменение статуса: " << endl;
	vehicleFleet[0].changeAvailableStatus();

	for (int i = 0; i < 6; i++) {
		vehicleFleet[i].printInfo();
	}

	cout << "\nОбновление пробега ==============================" << endl;
	vehicleFleet[0].updateMileage(500.0);
	vehicleFleet[0].updateMileage(-10.0);

	cout << "\nСтоимость топлива (при цене 3 руб/л) ============" << endl;
	for (int i = 0; i < 6; i++) {
		cout << "Транспорт " << vehicleFleet[i].getVehicleNumber()
			<< ": " << vehicleFleet[i].calculateFuelCost(3.0) << " руб." << endl;
	}

	return 0;
}