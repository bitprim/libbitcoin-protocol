/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_PROTOCOL_CONVERSION_HPP
#define LIBBITCOIN_PROTOCOL_CONVERSION_HPP

#include <memory>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/protocol/define.hpp>
#include <bitcoin/protocol/interface.pb.h>

namespace libbitcoin {
namespace protocol {

class BCP_API converter
{
public:

    virtual bool from_protocol(const std::string* hash,
        hash_digest& result);

    virtual bool from_protocol(const std::shared_ptr<std::string> hash,
        hash_digest& result);

    virtual bool from_protocol(const std::string* hash,
        short_hash& result);

    virtual bool from_protocol(const std::shared_ptr<std::string> hash,
        short_hash& result);

    virtual bool from_protocol(const point* point,
        chain::output_point& result);

    virtual bool from_protocol(const std::shared_ptr<point> point,
        chain::output_point& result);

    virtual bool from_protocol(const point* point,
        chain::input_point& result);

    virtual bool from_protocol(const std::shared_ptr<point> point,
        chain::input_point& result);

    virtual bool from_protocol(const tx_input* input,
        chain::input& result);

    virtual bool from_protocol(const std::shared_ptr<tx_input> input,
        chain::input& result);

    virtual bool from_protocol(const tx_output* output,
        chain::output& result);

    virtual bool from_protocol(const std::shared_ptr<tx_output> output,
        chain::output& result);

    virtual bool from_protocol(const tx* transaction,
        chain::transaction& result);

    virtual bool from_protocol(const std::shared_ptr<tx> transaction,
        chain::transaction& result);

    virtual bool from_protocol(const block_header* header,
        chain::header& result);

    virtual bool from_protocol(const std::shared_ptr<block_header> header,
        chain::header& result);

    virtual bool from_protocol(const block* block, chain::block& result);

    virtual bool from_protocol(const std::shared_ptr<block> block,
        chain::block& result);

    virtual bool to_protocol(const hash_digest& hash, std::string& result);

    virtual std::string* to_protocol(const hash_digest& hash);

    virtual bool to_protocol(const short_hash& hash, std::string& result);

    virtual std::string* to_protocol(const short_hash& hash);

    virtual bool to_protocol(const chain::output_point& point,
        protocol::point& result);

    virtual protocol::point* to_protocol(const chain::output_point& point);

    virtual bool to_protocol(const chain::input_point& point,
        protocol::point& result);

    virtual protocol::point* to_protocol(const chain::input_point& point);

    virtual bool to_protocol(const chain::input& input,
        tx_input& result);

    virtual tx_input* to_protocol(const chain::input& input);

    virtual bool to_protocol(const chain::output& output,
        tx_output& result);

    virtual tx_output* to_protocol(const chain::output& output);

    virtual bool to_protocol(const chain::transaction& transaction,
        tx& result);

    virtual tx* to_protocol(const chain::transaction& transaction);

    virtual bool to_protocol(const chain::header& header,
        block_header& result);

    virtual block_header* to_protocol(const chain::header& header);

    virtual bool to_protocol(const chain::block& block,
        protocol::block& result);

    virtual block* to_protocol(const chain::block& block);
};

}
}

#endif
