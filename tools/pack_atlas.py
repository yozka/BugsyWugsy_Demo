import os
from PIL import Image
import xml.etree.ElementTree as ET



#    Используется бибилотека 
#    pip3 install pillow


# Путь к директории с PNG файлами
directory = 'resources/packs2/'

# Путь куда будут записыватся атлас
directory_output = 'assets/'

# Файл атласа
atlas_png = 'textures/common2.png'

# Файл описания атласа
atlas_xml = 'textures/common2.xml'

# Группа куда загружаются текстуры
group = "common2"

# отступы между спрайтами
space = 0 

#
#
# Создание нового атласа текстур
atlas_width, atlas_height = 512, 512  # Размеры атласа
atlas = Image.new('RGBA', (atlas_width, atlas_height))
current_x = space
current_y = space
max_height = 0

# Создание корневого элемента XML
resources = ET.Element('resources')
atlas_element = ET.SubElement(resources, 'atlas', imagePath=atlas_png, group=group)

# Сканирование директории и добавление файлов в атлас
for dirpath, dirnames, filenames in os.walk(directory):
    for filename in filenames:
        if filename.endswith('.png'):
            # Открытие изображения
            img_path = os.path.join(dirpath, filename)
            with Image.open(img_path) as img:
                # Проверка на превышение размера атласа
                if current_x + img.width + space > atlas_width:
                    current_x = space
                    current_y += max_height
                    max_height = 0

                # Вставка изображения в атлас
                atlas.paste(img, (current_x, current_y))

                # Создание элемента SubTexture в XML
                name = img_path.replace(directory, '')
                subtexture = ET.SubElement(atlas_element, 'SubTexture', name=name, x=str(current_x), y=str(current_y), width=str(img.width), height=str(img.height))

                # Обновление координат для следующего изображения
                current_x += img.width + space
                if img.height > max_height:
                    max_height = img.height + space

# Сохранение атласа текстур
atlas.save(directory_output + atlas_png)

# Форматирование xml
def indent(elem, level=0):
    i = "\n" + level*"\t"
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "\t"
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            indent(elem, level+1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i
# //

# Генерация XML
indent(resources)
tree = ET.ElementTree(resources)
tree.write(directory_output + atlas_xml, encoding='utf-8', xml_declaration=True)
