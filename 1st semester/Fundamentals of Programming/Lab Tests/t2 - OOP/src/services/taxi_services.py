class TaxiService:
    def __init__(self, driver_repo, address_repo):
        self.__driver_repo = driver_repo
        self.__address_repo = address_repo

    def manhattan_distance(self, x1, y1, x2, y2):
        return abs(x1 - x2) + abs(y1 - y2)

    def get_sorted_drivers(self):
        drivers = self.__driver_repo.list_all()
        return sorted(drivers, key=lambda d: d.get_name())

    def get_sorted_addresses(self):
        addresses = self.__address_repo.list_all()
        return sorted(addresses, key=lambda a: a.get_name())

    def drivers_by_distance_to_address_id(self, address_id):
        addresses = self.__address_repo.list_all()
        drivers = self.__driver_repo.list_all()

        address = None
        for a in addresses:
            if a.get_id() == address_id:
                address = a
                break

        if address is None:
            raise ValueError("Address not found")

        result = []
        for d in drivers:
            dist = self.manhattan_distance(
                d.get_x(), d.get_y(),
                address.get_x(), address.get_y()
            )
            result.append((d, dist))

        result.sort(key=lambda pair: pair[1])
        return result

    def closest_driver_for_each_address(self):
        drivers = self.__driver_repo.list_all()
        addresses = self.__address_repo.list_all()

        results = []

        for address in addresses:
            closest_driver = drivers[0]
            min_dist = self.manhattan_distance(
                drivers[0].get_x(), drivers[0].get_y(),
                address.get_x(), address.get_y()
            )

            for d in drivers[1:]:
                dist = self.manhattan_distance(
                    d.get_x(), d.get_y(),
                    address.get_x(), address.get_y()
                )
                if dist < min_dist:
                    min_dist = dist
                    closest_driver = d

            results.append((address, closest_driver, min_dist))

        results.sort(key=lambda x: x[2], reverse=True)
        return results
