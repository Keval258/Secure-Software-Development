import uuid
import re
import copy

class Inventory:
    MAX_ITEM_NAME_LENGTH = 100  # Maximum length for an item name
    ALLOWED_ITEM_NAME_CHARACTERS = r'^[A-Za-z0-9\s-]{1,50}$'

    def __init__(self):
        self._items = {
            "Item 1": 10.0,
            "Item 2": 15.0,
            "Item 3": 20.0
        }

    def add_item(self, item_id, item_name):
        if len(item_name) <= self.MAX_ITEM_NAME_LENGTH and re.match(self.ALLOWED_ITEM_NAME_CHARACTERS, item_name):
            self._items[item_id] = item_name
        else:
            raise ValueError("Invalid item name")

    def get_item_cost(self, item_id):
        cost = self._items.get(item_id)
        if cost is None or cost < 0.01:
            raise ValueError("Invalid cost for item '{}' in the inventory.".format(item_id))
        return cost


class ShoppingCart:
    MAX_QUANTITY = 20  # Maximum allowed quantity for an item in the cart

    def __init__(self, customer_id):
        self._cart_id = str(uuid.uuid4())
        self._customer_id = customer_id
        self._items = {}

        if self.validate_customer_id(customer_id):
            self._customer_id = customer_id
        else:
            raise ValueError("Invalid customer ID")

    @property
    def cart_id(self):
        return self._cart_id

    @property
    def customer_id(self):
        return self._customer_id

    @property
    def items(self):
        return copy.deepcopy(self._items)

    def add_item(self, item_id, quantity):
        if quantity <= 0:
            raise ValueError("Invalid quantity. Quantity must be greater than zero.")

        if item_id in self._items:
            self._items[item_id] = min(self._items[item_id] + quantity, self.MAX_QUANTITY)
        else:
            self._items[item_id] = min(quantity, self.MAX_QUANTITY)

    def update_item_quantity(self, item_id, quantity):
        if quantity <= 0:
            raise ValueError("Invalid quantity. Quantity must be greater than zero.")

        if item_id in self._items:
            self._items[item_id] = min(quantity, self.MAX_QUANTITY)
        else:
            raise ValueError("Item not found in cart")

    def remove_item(self, item_id, quantity):
        if quantity <= 0:
            raise ValueError("Invalid quantity. Quantity must be greater than zero.")

        if item_id in self._items:
            self._items[item_id] -= quantity
            if self._items[item_id] <= 0:
                del self._items[item_id]
        else:
            raise ValueError("Item not found in cart")

    def get_total_quantity(self):
        return sum(self._items.values())

    def get_total_cost(self, inventory):
        total_cost = 0
        for item_id, quantity in self._items.items():
            item_cost = inventory.get_item_cost(item_id)
            total_cost += item_cost * quantity
        return total_cost

    def validate_customer_id(self, customer_id):
        # customer ID format (3 letters, 5 numbers, 2 letters, a dash, and finally an A or a Q)
        if re.match(r'^[A-Za-z]{3}\d{5}[A-Za-z]{2}[-][AQ]$', customer_id):
            return True
        else:
            return False


# Example usage
inventory = Inventory()
cart = ShoppingCart("ROY12345KP-A")
cart.add_item("Item 1", 1)
cart.add_item("Item 2", 1)
cart.add_item("Item 3", 1)
total_cost = cart.get_total_cost(inventory)
print("Total cost: ${:.2f}".format(total_cost))
