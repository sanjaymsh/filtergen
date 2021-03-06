/* iptables-save syntax tree data structure definitions
 *
 * Copyright (c) 2003,2004 Jamie Wilkinson <jaq@spacepants.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __IPTABLES_AST_H__
#define __IPTABLES_AST_H__

struct pkt_count_s {
  char *in;
  char *out;
};

struct identifier_s {
  char *string;
};

struct not_identifier_s {
  int neg;
  struct identifier_s *identifier;
};

struct range_s {
  struct identifier_s *start;
  struct identifier_s *end;
};

struct not_range_s {
  int neg;
  struct range_s *range;
};

struct in_interface_option_s {
  struct not_identifier_s *not_identifier;
};

struct jump_option_s {
  struct identifier_s *identifier;
};

struct destination_option_s {
  struct not_identifier_s *not_identifier;
};

struct protocol_option_s {
  struct identifier_s *identifier;
};

struct match_option_s {
  struct identifier_s *identifier;
};

struct dport_option_s {
  struct not_range_s *not_range;
  struct not_identifier_s *not_identifier;
};

struct to_ports_option_s {
  struct identifier_s *identifier;
};

struct source_option_s {
  struct not_identifier_s *not_identifier;
};

struct out_interface_option_s {
  struct not_identifier_s *not_identifier;
};

struct to_source_option_s {
  struct identifier_s *identifier;
};

struct state_option_s {
  struct identifier_s *identifier;
};

struct limit_option_s {
  struct identifier_s *identifier;
};

struct log_prefix_option_s {
  struct identifier_s *identifier;
};

struct sport_option_s {
  struct not_range_s *not_range;
  struct not_identifier_s *not_identifier;
};

struct uid_owner_option_s {
  struct identifier_s *identifier;
};

struct tcp_flags_option_s {
  struct identifier_s *flags;
  struct identifier_s *mask;
};

struct reject_with_option_s {
  struct identifier_s *identifier;
};

struct icmp_type_option_s {
  struct identifier_s *identifier;
};

struct fragment_option_s {
  int i;
};

struct clamp_mss_to_pmtu_option_s {
  int i;
};

struct helper_option_s {
  struct identifier_s *identifier;
};

struct syn_option_s {
  int i;
};

struct option_s {
  struct in_interface_option_s *in_interface_option;
  struct jump_option_s *jump_option;
  struct destination_option_s *destination_option;
  struct protocol_option_s *protocol_option;
  struct match_option_s *match_option;
  struct dport_option_s *dport_option;
  struct to_ports_option_s *to_ports_option;
  struct source_option_s *source_option;
  struct out_interface_option_s *out_interface_option;
  struct to_source_option_s *to_source_option;
  struct state_option_s *state_option;
  struct limit_option_s *limit_option;
  struct log_prefix_option_s *log_prefix_option;
  struct sport_option_s *sport_option;
  struct uid_owner_option_s *uid_owner_option;
  struct tcp_flags_option_s *tcp_flags_option;
  struct reject_with_option_s *reject_with_option;
  struct icmp_type_option_s *icmp_type_option;
  struct fragment_option_s *fragment_option;
  struct clamp_mss_to_pmtu_option_s *clamp_mss_to_pmtu_option;
  struct helper_option_s *helper_option;
  struct syn_option_s *syn_option;
};

struct not_option_s {
  int neg;
  struct option_s *option;
};

struct option_list_s {
  struct option_list_s *option_list;
  struct not_option_s *not_option;
};

struct rule_s {
  char *chain;
  char *policy;
  struct pkt_count_s *pkt_count;
  struct option_list_s *option_list;
};

struct rule_list_s {
  struct rule_list_s *list;
  struct rule_s *rule;
};

struct table_s {
  char *name;
  struct rule_list_s *rule_list;
};

struct table_list_s {
  struct table_list_s *list;
  struct table_s *table;
};

struct ast_s {
  struct table_list_s *list;
};

#endif /* __IPTABLES_AST_H__ */
